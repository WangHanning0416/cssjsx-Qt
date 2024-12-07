#ifndef BOOKKEEPING_H
#define BOOKKEEPING_H

#include <QWidget>
#include <QtCharts/QChartGlobal>
#include <QLCDNumber>
#include <QLabel>
#include <QComboBox>
#include <QScrollArea>
#include <QtCharts>
#include <QtCharts/QPieSlice>
#include <QProcess>
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include "createpage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

/*
QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QAbstractSeries;
class QPieSlice;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE
*/
class CreatePage;
class DrilldownSlice : public QPieSlice
{
    Q_OBJECT

public:
    DrilldownSlice(qreal value, QString prefix, QAbstractSeries *drilldownSeries);
    virtual ~DrilldownSlice();
    QAbstractSeries *drilldownSeries() const;

public Q_SLOTS:
    void updateLabel();
    void showHighlight(bool show);

private:
    QAbstractSeries *m_drilldownSeries;
    QString m_prefix;
};

class DrilldownChart : public QChart
{
    Q_OBJECT
public:
    explicit DrilldownChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = {});
    ~DrilldownChart();
    void changeSeries(QAbstractSeries *series);

public Q_SLOTS:
    void handleSliceClicked(QPieSlice *slice);

private:
    QAbstractSeries *m_currentSeries;
};

class item
{
public:
    bool in_out;
    QString type;
    double money;
    QString note;
    int month,date;
    int id;
    item(bool in_out_, QString type_, double money_, int month_, int date_, QString note_);
    item(const item& it);
    item();
    ~item() {};
};

class Day
{
public:
    std::vector<item> items;
    double day_in,day_out;
    void insert_item(bool in_out_, QString type_, double money_, int month_, int date_, QString note_);
    int items_num;
    Day();
    Day(const Day& d);
    ~Day();
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    CreatePage *createpage = NULL;
    QLabel * timeShow();
    QLabel * totalShow();
    QChartView * sevendaysShow();
    QScrollArea * itemsShow();

    QLabel * labelTotal;
    QChartView * chartView;
    QScrollArea * scrollArea;

    QWidget * itemsWidget;
    void itemsWidgetShow();
    void createWidgetShow();
    int count;
    void get_total_inout(int m,int d);
    QLabel * counterLabel;
    void renew();

    QWidget * wSecondLayout;
    QVBoxLayout * layout ;
private:
    Ui::Widget *ui;

private slots:
    void timerUpdate();
    void renewit();
};
class DataBase : public QObject{
    Q_OBJECT
public:
    DataBase(QString name, QObject *parent=0);
    ~DataBase();

public:
    bool insertData(Day data);
    bool getDataList(Day a[]);
    bool update(Day data);
    bool deleteAllData();
    QSqlDatabase m_DataBase;
    bool initTable();
    bool isExistTable(QString table);
    bool createTable(QString table);
};

extern Day Days[100];
extern item NowEditing;
extern double total_in,total_out,pure;
extern DataBase db;

#endif // BOOKKEEPING_H
