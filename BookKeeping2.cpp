#include "BookKeeping2.h"
#include "ui_BookKeeping2.h"
#include "createpage.h"
#include "accountpage.h"
#include "set_badget.h"
#include <iostream>
#include <QApplication>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFont>
#include <vector>
#include <QComboBox>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QScrollArea>
#include <QString>
#include <QTime>
#include <QTimer>
#include <QPushButton>
#include <QSpinBox>
#include <QtCharts/QLegend>
#include <QtCharts/QPieSeries>
#include <QMessageBox>
#include <QPixmap>
#include <QPalette>
#include <QDate>
#include <QCoreApplication>
#include <QDebug>
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
//#include <QSqlRecord>
double total_in=0,total_out=0;
double pure=total_in-total_out;
Day Days[100];
item NowEditing;
int NowDate=0,NowMonth=0;
DataBase db("days");

void Widget::timerUpdate(){
    QDateTime currentDateTime = QDateTime::currentDateTime();
    // 设置日期和时间格式
    QString dateTimeString = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
    // 更新标签显示的日期和时间
    QLabel *dateTimeLabel = findChild<QLabel *>();
    if (dateTimeLabel) {
        dateTimeLabel->setText(dateTimeString);
    }
    int y=0,m=0,d=0;
    QDate::currentDate().getDate(&y,&m,&d);
    NowDate=d;NowMonth=m;
}

void Widget::renew(){
    this->close();
    count++;
    delete labelTotal;
    delete chartView;
    delete scrollArea;
    counterLabel->setNum(count);
    labelTotal = new QLabel;
    labelTotal = totalShow();
    layout->addWidget(labelTotal);
    chartView = new QChartView;
    chartView = sevendaysShow();
    layout->addWidget(chartView);
    scrollArea = new QScrollArea;
    scrollArea = itemsShow();
    layout->addWidget(scrollArea);
    this->show();
}

item::item(): in_out(0), type(""), money(0), note(""), id(0)
{
    QDate current_date=QDate::currentDate();
    int month_,date_,year_;
    current_date.getDate(&year_,&month_,&date_);
    month=month_;
    date=date_;
}
item::item(const item& it):
    in_out(it.in_out), type(it.type), money(it.money), note(it.note), month(it.month), date(it.date), id(it.id)
    {};

QLabel *item_show(Day &d, int i) {
    QFont font("Helvetica Neue", 20);

    QLabel *label = new QLabel;

    QString result;
    if (d.items[i].in_out == false) {
        result = QString(
                     "<div style='text-align: center;'>"
                     "<p style='margin: 0;'>日期：<span style='font-weight: bold;'>%1 月 %2 日</span></p>"
                     "<p style='margin: 0;'><span style='font-weight: bold;'>类别：</span>%3 <span style='color: #2d7d46;'>+%4 元</span></p>"
                     "</div>"
                     ).arg(d.items[i].month).arg(d.items[i].date).arg(d.items[i].type).arg(d.items[i].money);
    } else {
        result = QString(
                     "<div style='text-align: center;'>"
                     "<p style='margin: 0;'>日期：<span style='font-weight: bold;'>%1 月 %2 日</span></p>"
                     "<p style='margin: 0;'><span style='font-weight: bold;'>类别：</span>%3 <span style='color: #d9534f;'>-%4 元</span></p>"
                     "</div>"
                     ).arg(d.items[i].month).arg(d.items[i].date).arg(d.items[i].type).arg(d.items[i].money);
    }

    label->setText(result);
    label->setFont(font);
    label->setFrameShape(QFrame::NoFrame);

    QString styleSheet = R"(
        QLabel {
            background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #ffffff, stop:1 #f9f9f9);
            border: 1px solid #dddddd;
            border-radius: 12px;
            padding: 15px;
            color: #333333;
            font-size: 23px;
            box-shadow: 0px 4px 8px rgba(0, 0, 0, 0.1);
        }
        QLabel div {
            line-height: 1.5;
        }
    )";

    label->setStyleSheet(styleSheet);

    label->setAlignment(Qt::AlignCenter);
    label->setGeometry(10, 10, 400, 100);

    return label;
}


item::item(bool in_out_, QString type_, double money_, int month_, int date_, QString note_):
    in_out(in_out_), type(type_), money(money_), note(note_), month(month_), date(date_)
{
    if(in_out == true){total_in+=money;pure+=money;}
    else {total_out+=money;pure-=money;}
}

Day::Day(const Day& d): day_in(d.day_in), day_out(d.day_out), items_num(d.items_num)
{
    items.clear();
    typedef std::vector<item>::const_iterator iter;
    for(iter i=d.items.begin();i!=d.items.end();i++)
        items.push_back(*i);
}
Day::~Day() {};
Day::Day(){
    day_in = 0;day_out = 0;
    items_num = 0;
}

void Day::insert_item(bool in_out_, QString type_, double money_, int month_, int date_, QString note_)
{
    item it(in_out_,type_,money_,month_,date_,note_);
    items.push_back(it);
    items_num++;
    if(it.in_out==0) day_in+=it.money;
    else day_out+=it.money;
}

QLabel * Widget::timeShow(){
    QFont font2;
    font2.setPointSize(15);
    font2.setFamily("SimHei");

    QLabel *timeLabel = new QLabel(this);
    timeLabel->setFont(font2);
    timeLabel->setGeometry(10, 10, 300, 10);

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);

    int y=0,m=0,d=0;
    QDate::currentDate().getDate(&y,&m,&d);
    NowDate=d;NowMonth=m;

    return timeLabel;
}

QLabel *Widget::totalShow() {
    // 设置字体和大小
    QFont font("Helvetica Neue", 23); // 字体和大小保持一致

    QLabel *labelTotal = new QLabel;
    QString totalMoney = QString("<div style='text-align: left; font-family: Helvetica Neue; font-size: 23px;'>"
                                 "<span style='font-size: 18px; font-weight: bold;'>财务总览</span><br>"
                                 "<span style='color: #666666;'>总收入：</span><span style='color: #2ecc71;'>%1元</span><br>"
                                 "<span style='color: #666666;'>总支出：</span><span style='color: #e74c3c;'>%2元</span><br>"
                                 "<span style='color: #666666;'>净收入：</span><span style='color: #3498db;'>%3元</span>"
                                 "</div>")
                             .arg(total_in).arg(total_out).arg(pure);
    labelTotal->setText(totalMoney);
    labelTotal->setFont(font);
    labelTotal->setAlignment(Qt::AlignLeft); // 居左对齐
    labelTotal->setStyleSheet("background-color: #f0f0f0; border-radius: 10px; padding: 10px;");
    labelTotal->setFixedSize(400, 120);

    return labelTotal;
}

QChartView *Widget::sevendaysShow() {
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QDateTime beginDateTime = QDateTime::fromString("2024-04-30 00:00:00", "yyyy-MM-dd hh:mm:ss");
    int n = beginDateTime.daysTo(currentDateTime);

    // 创建数据集
    QBarSet *set1 = new QBarSet("收入");
    QBarSet *set0 = new QBarSet("支出");
    *set0 << Days[n-6].day_in << Days[n-5].day_in << Days[n-4].day_in << Days[n-3].day_in << Days[n-2].day_in << Days[n-1].day_in << Days[n].day_in;
    *set1 << Days[n-6].day_out << Days[n-5].day_out << Days[n-4].day_out << Days[n-3].day_out << Days[n-2].day_out << Days[n-1].day_out << Days[n].day_out;

    // 计算最大值
    double day_in_max = std::max({Days[n-6].day_in, Days[n-5].day_in, Days[n-4].day_in, Days[n-3].day_in, Days[n-2].day_in, Days[n-1].day_in, Days[n].day_in});
    double day_out_max = std::max({Days[n-6].day_out, Days[n-5].day_out, Days[n-4].day_out, Days[n-3].day_out, Days[n-2].day_out, Days[n-1].day_out, Days[n].day_out});
    int money_max = std::max(10, static_cast<int>(std::max(day_in_max, day_out_max)));

    // 创建柱状图系列
    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);

    // 创建图表
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("近七日收支情况");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // 设置轴
    QStringList categories;
    categories << "day1" << "day2" << "day3" << "day4" << "day5" << "day6" << "day7";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, money_max);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // 设置图表视图
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // 设置图表样式
    QString styleSheet = R"(
        QChart {
            background-color: #ffffff; /* 设置背景色为白色 */
            border: none; /* 去除边框 */
        }
        QBarSet {
            color: #5DA5DA; /* 设置收入柱状图颜色 */
        }
        QBarSet:bar:alternate {
            color: #FAA43A; /* 设置支出柱状图颜色 */
        }
        QLegend {
            font-size: 12px; /* 调整图例字体大小 */
        }
    )";
    chartView->setStyleSheet(styleSheet);

    return chartView;
}

QScrollArea * Widget::itemsShow(){
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QDateTime beginDateTime = QDateTime::fromString("2024-04-30 00:00:00", "yyyy-MM-dd hh:mm:ss");
    int n = beginDateTime.daysTo(currentDateTime);

    QScrollArea * scrollArea = new QScrollArea;
    scrollArea->setGeometry(0,0,400,200);
    QWidget  * w_tmp = new QWidget(this);
    int t = Days[n].items_num+Days[n-1].items_num+Days[n-2].items_num+Days[n-3].items_num+Days[n-4].items_num+Days[n-5].items_num+Days[n-6].items_num;

    w_tmp->setGeometry(0,0,600,t*120);

    QVBoxLayout * layout2 = new QVBoxLayout(w_tmp);
    for(int i=0;i<Days[n].items_num;i++) layout2->addWidget(item_show(Days[n],i));
    for(int i=0;i<Days[n-1].items_num;i++) layout2->addWidget(item_show(Days[n-1],i));
    for(int i=0;i<Days[n-2].items_num;i++) layout2->addWidget(item_show(Days[n-2],i));
    for(int i=0;i<Days[n-3].items_num;i++) layout2->addWidget(item_show(Days[n-3],i));
    for(int i=0;i<Days[n-4].items_num;i++) layout2->addWidget(item_show(Days[n-4],i));
    for(int i=0;i<Days[n-5].items_num;i++) layout2->addWidget(item_show(Days[n-5],i));
    for(int i=0;i<Days[n-6].items_num;i++) layout2->addWidget(item_show(Days[n-6],i));

    scrollArea->setWidget(w_tmp);

    return scrollArea;
}

DrilldownSlice::DrilldownSlice(qreal value, QString prefix, QAbstractSeries *drilldownSeries)
    : m_drilldownSeries(drilldownSeries),
    m_prefix(prefix)
{
    setValue(value);
    updateLabel();
    setLabelFont(QFont("Arial", 8));
    connect(this, &DrilldownSlice::percentageChanged, this, &DrilldownSlice::updateLabel);
    connect(this, &DrilldownSlice::hovered, this, &DrilldownSlice::showHighlight);
}

DrilldownSlice::~DrilldownSlice()
{

}

QAbstractSeries *DrilldownSlice::drilldownSeries() const
{
    return m_drilldownSeries;
}

void DrilldownSlice::updateLabel()
{
    QString label = m_prefix;
    label += " $";
    label += QString::number(this->value());
    label += ", ";
    label += QString::number(this->percentage() * 100, 'f', 1);
    label += "%";
    setLabel(label);
}

void DrilldownSlice::showHighlight(bool show)
{
    setLabelVisible(show);
    setExploded(show);
}

DrilldownChart::DrilldownChart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QChart(QChart::ChartTypeCartesian, parent, wFlags),
    m_currentSeries(0)
{

}

DrilldownChart::~DrilldownChart()
{

}

void DrilldownChart::changeSeries(QAbstractSeries *series)
{
    // NOTE: if the series is owned by the chart it will be deleted
    // here the "window" owns the series...
    if (m_currentSeries)
        removeSeries(m_currentSeries);
    m_currentSeries = series;
    addSeries(series);
    setTitle(series->name());
}

void DrilldownChart::handleSliceClicked(QPieSlice *slice)
{
    DrilldownSlice *drilldownSlice = static_cast<DrilldownSlice *>(slice);
    changeSeries(drilldownSlice->drilldownSeries());
}

void Widget::itemsWidgetShow(){
    itemsWidget = new QWidget;
    QVBoxLayout * layout = new QVBoxLayout(itemsWidget);

    DrilldownChart *chart = new DrilldownChart();
    chart->setTheme(QChart::ChartThemeLight);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
    QPieSeries *yearSeries = new QPieSeries();
    yearSeries->setName("各月消费情况");
    const QStringList months = {
        "三餐", "零食", "衣服", "交通", "日用品", "医疗", "学习/工作", "娱乐", "其他"
    };
    const QStringList names = {
        "1月", "2月", "3月", "4月", "5月","6月","7月","8月","9月","10月","11月","12月"
    };
    for (const QString &name : names) {
        QPieSeries *series = new QPieSeries();
        series->setName("月季各种类消费情况 " + name);

        for (const QString &month : months)
            *series << new DrilldownSlice(QRandomGenerator::global()->bounded(100), month, yearSeries);

        QObject::connect(series, &QPieSeries::clicked, chart, &DrilldownChart::handleSliceClicked);

        *yearSeries << new DrilldownSlice(series->sum(), name, series);
    }
    QObject::connect(yearSeries, &QPieSeries::clicked, chart, &DrilldownChart::handleSliceClicked);
    chart->changeSeries(yearSeries);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(chartView);

    DrilldownChart *nchart = new DrilldownChart();
    nchart->setTheme(QChart::ChartThemeBrownSand);
    nchart->setAnimationOptions(QChart::AllAnimations);
    nchart->legend()->setVisible(true);
    nchart->legend()->setAlignment(Qt::AlignRight);
    QPieSeries *nyearSeries = new QPieSeries();
    nyearSeries->setName("各月收入情况");
    const QStringList nmonths = {
        "工资", "生活费", "外快"
    };
    const QStringList nnames = {
        "1月", "2月", "3月", "4月", "5月","6月","7月","8月","9月","10月","11月","12月"
    };
    for (const QString &name : nnames) {
        QPieSeries *nseries = new QPieSeries();
        nseries->setName("月季各种类收入情况 " + name);

        for (const QString &month : nmonths)
            *nseries << new DrilldownSlice(QRandomGenerator::global()->bounded(100), month, nyearSeries);

        QObject::connect(nseries, &QPieSeries::clicked, nchart, &DrilldownChart::handleSliceClicked);

        *nyearSeries << new DrilldownSlice(nseries->sum(), name, nseries);
    }
    QObject::connect(nyearSeries, &QPieSeries::clicked, nchart, &DrilldownChart::handleSliceClicked);
    nchart->changeSeries(nyearSeries);
    QChartView *nchartView = new QChartView(nchart);
    nchartView->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(nchartView);

    itemsWidget->resize(1000,1000);
    itemsWidget->show();
}

void Widget::createWidgetShow() {
    this->createpage->show();
}

void accountshow(){
    AccountPage *w = new AccountPage();
    w->show();
}

void newBudgetShow(){
    set_badget * w = new set_badget;
    w->show();
}

void Widget::renewit() {
    this->renew();
}

DataBase::DataBase(QString name, QObject *parent)
    : QObject(parent)
{
    if (QSqlDatabase::contains(name)) {
        m_DataBase = QSqlDatabase::database(name);
        qDebug() << "exist";
    } else {
        m_DataBase = QSqlDatabase::addDatabase("QSQLITE");
        m_DataBase.setDatabaseName(name + ".db");
    }
    initTable();
}

DataBase::~DataBase()
{
}

bool DataBase::initTable()
{
    if (!m_DataBase.open()) {
        return false;
    }

    if (!isExistTable("days")) {
        createTable("days");
    }
    return false;
}

bool DataBase::isExistTable(QString table)
{
    bool bRet = false;
    if (!m_DataBase.open()) {
        return bRet;
    }
    QSqlQuery query(m_DataBase);
    query.exec(QString("select count(*) from sqlite_master where type='table' and name='%1'").arg(table));
    if (query.next()) {
        if (query.value(0).toInt() > 0) {
            bRet = true;
        }
    }
    return bRet;
}

bool DataBase::createTable(QString table)
{
    if (!m_DataBase.open()) {
        return false;
    }

    QSqlQuery query(m_DataBase);
    if (table == QString("days")) {
        bool success = query.exec("CREATE TABLE days ("
                                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                  "item_in_out INTEGER NOT NULL, "
                                  "item_money REAL NOT NULL, "
                                  "item_date INTEGER NOT NULL, "
                                  "item_month INTEGER NOT NULL, "
                                  "item_id INTEGER NOT NULL, "
                                  "day_in REAL NOT NULL, "
                                  "day_out REAL NOT NULL, "
                                  "items_num INTEGER NOT NULL, "
                                  "item_type VARCHAR(40) NOT NULL)");

        if (success) {
            return true;
        } else {
            QSqlError lastError = query.lastError();
            QString err = lastError.driverText();
            return false;
        }
    } else {
        return false;
    }
}

bool DataBase::insertData(Day data)
{
    if (!m_DataBase.open()) {
        return false;
    }
    int size = data.items.size();
    //if (size > 0) qDebug() << size;
    for (int i = 0; i < size; i++) {
        QSqlQuery query(m_DataBase);
        bool success = query.exec(QString("INSERT INTO days (item_in_out, item_money, item_date, item_month, item_id, day_in, day_out, items_num, item_type) "
                                          "VALUES (%1, %2, %3, %4, %5, %6, %7, %8, '%9')")
                                      .arg(data.items[i].in_out)
                                      .arg(data.items[i].money)
                                      .arg(data.items[i].date)
                                      .arg(data.items[i].month)
                                      .arg(data.items[i].id)
                                      .arg(data.day_in)
                                      .arg(data.day_out)
                                      .arg(data.items_num)
                                      .arg(data.items[i].type));

        if (!success) {
            QSqlError lastError = query.lastError();
            QString err = lastError.driverText();
            return false;
        }
    }

    return true;
}

bool DataBase::deleteAllData()
{
    if (!m_DataBase.open()) {
        return false;
    }

    QSqlQuery query(m_DataBase);
    bool success = query.exec("DELETE FROM days");

    if (!success) {
        QSqlError lastError = query.lastError();
        QString err = lastError.driverText();
        return false;
    }
    return true;
}


bool DataBase::getDataList(Day a[])
{
    if (!m_DataBase.open()) {
        return false;
    }
    QSqlQuery query(m_DataBase);
    query.prepare(QString("SELECT * FROM days"));
    query.exec();
    bool t = 0;
    while (query.next()) {
        int Day_id = 0;
        int d, m;
        item newitem;
        d = query.value("item_date").toInt();
        m = query.value("item_month").toInt();
        newitem.date = d; newitem.month = m;
        switch(m)
        {
        case 5:Day_id=d;break;
        case 6:Day_id=d+31;break;
        case 7:Day_id=d+61;break;
        default:break;
        }
        newitem.money = query.value("item_money").toDouble();
        newitem.in_out = query.value("item_in_out").toBool();
        if(newitem.in_out == 0) total_in += newitem.money;
        if(newitem.in_out == 1) total_out += newitem.money;
        newitem.id = query.value("item_id").toInt();
        newitem.type = query.value("item_type").toString();
        qDebug() << total_in << ' ' << newitem.id << ' ' << query.value("id").toInt();
        a[Day_id].items.push_back(newitem);
        a[Day_id].day_in = query.value("day_in").toDouble();
        a[Day_id].day_out = query.value("day_out").toDouble();
        //if (a[Day_id].day_in > 0) {qDebug() << a[Day_id].day_in; t = 1;}
        a[Day_id].items_num = query.value("items_num").toInt();
    }
    //if (t == 0) qDebug() << "no";
    return true;
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , count(0)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    db.getDataList(Days);
    this->createpage = new CreatePage;
    connect(this->createpage->inpage, SIGNAL(saved()), this, SLOT(renewit()));
    connect(this->createpage->outpage, SIGNAL(saved()), this, SLOT(renewit()));
    Days[29].insert_item(1,"外卖",46,5,29,"");
    Days[30].insert_item(0,"外快",25,5,30,"");
    Days[30].insert_item(0,"工资",125,5,30,"");
    Days[27].insert_item(0,"工资",75,5,39,"");
    Days[28].insert_item(1,"外卖",79,5,28,"");
    /*//时间显示
    QLabel * l = timeShow();
    layout->addWidget(l);*/

    QWidget * wFirstLayout = new QWidget;
    QVBoxLayout * firstLayout = new QVBoxLayout(wFirstLayout);

    //账号界面
    QPushButton * newHaoButton = new QPushButton;
    newHaoButton->setText("账号");
    newHaoButton->setStyleSheet("background-color: white;");
    connect(newHaoButton,&QPushButton::clicked,this,accountshow);
    firstLayout->addWidget(newHaoButton);
    //详细查看界面
    QPushButton * newWidgetButton = new QPushButton;
    newWidgetButton->setText("查看");
    newWidgetButton->setStyleSheet("background-color: white;");
    connect(newWidgetButton,&QPushButton::clicked,this,&Widget::itemsWidgetShow);
    firstLayout->addWidget(newWidgetButton);
    //新建界面
    QPushButton * newNewButton = new QPushButton;
    newNewButton->setText("新建");
    newNewButton->setStyleSheet("background-color: white;");
    connect(newNewButton,&QPushButton::clicked,this,&Widget::createWidgetShow);
    firstLayout->addWidget(newNewButton);
    //打卡界面
    QPushButton * newBudgetButton = new QPushButton;
    newBudgetButton->setText("预算");
    connect(newBudgetButton,&QPushButton::clicked,this,newBudgetShow);
    newBudgetButton->setStyleSheet("background-color: white;");
    firstLayout->addWidget(newBudgetButton);
    //刷新按钮
    QPushButton * newShuaButton = new QPushButton;
    newShuaButton->setText("刷新");
    connect(newShuaButton,&QPushButton::clicked,this,&Widget::renew);
    newShuaButton->setStyleSheet("background-color: white;");
    firstLayout->addWidget(newShuaButton);

    counterLabel = new QLabel(QString::number(count), this);
    firstLayout->addWidget(counterLabel);

    firstLayout->setAlignment(Qt::AlignTop);
    wFirstLayout->setStyleSheet("background-color: rgba(255, 255, 255, 0);");

    wSecondLayout = new QWidget;
    layout = new QVBoxLayout(wSecondLayout);
    //总支出总收入显示
    labelTotal = new QLabel;
    labelTotal = totalShow();
    layout->addWidget(labelTotal);

    //近七天数据显示
    chartView = new QChartView;
    chartView = sevendaysShow();
    layout->addWidget(chartView);

    //近期消费条目
    scrollArea = new QScrollArea;
    scrollArea = itemsShow();
    layout->addWidget(scrollArea);

    QHBoxLayout * Total = new QHBoxLayout(this);

    Total->addWidget(wFirstLayout);
    Total->addWidget(wSecondLayout);
    wSecondLayout->setStyleSheet("background-color: rgba(255, 255, 255, 100);");

    QPixmap pixmap("C:\\Users\\whn04\\Desktop\\185053eawmecvrwrwp1urk.jpg");
    QPalette palette;
    palette.setBrush(QPalette::Window,pixmap);
    this->setPalette(palette);

    this->resize(835,1000);
}


Widget::~Widget()
{
    delete ui;
}
