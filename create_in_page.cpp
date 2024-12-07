#include <QDate>
#include "create_in_page.h"
#include "ui_create_in_page.h"
#include "BookKeeping2.h"
//item NowEditing;
Create_in_Page::Create_in_Page(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Create_in_Page)
{
    ui->setupUi(this);
}

Create_in_Page::~Create_in_Page()
{
    delete ui;
}

void Create_in_Page::on_pushButton_save_clicked()
{
    //qDebug() << Days[31].day_in;
    int m=0,y=0,d=0;
    QDate::currentDate().getDate(&y,&m,&d);
    NowEditing.date=d;
    NowEditing.month=m;
    NowEditing.in_out=0;
    int Day_id=0;
    switch(m)
    {
    case 5:Day_id=d;break;
    case 6:Day_id=d+31;break;
    case 7:Day_id=d+61;break;
    default:break;
    }
    NowEditing.id=Days[Day_id].items_num;
    Days[Day_id].items.push_back(NowEditing);
    Days[Day_id].items_num++;
    Days[Day_id].day_in+=NowEditing.money;
    total_in+=NowEditing.money;
    pure=total_in-total_out;
    update();
    if(!db.deleteAllData()) qDebug() << "delete fail";
    for (int i = 1; i <= 92; i++) {
        if (!db.insertData(Days[i])) qDebug() << "insert fail " << i;
    }
    Day a[100];
    //if (!db.getDataList(a)) qDebug() << "getdata fail";
    qDebug() << a[31].day_in;
    emit this->saved();
    this->close();
    //emit this->back();
}


void Create_in_Page::on_pushButton_cancel_clicked()
{
    emit this->back();
}
void Create_in_Page::on_doubleSpinBox_valueChanged(double arg1)
{
    NowEditing.money=arg1;
}


void Create_in_Page::on_comboBox_currentTextChanged(const QString &arg1)
{
    NowEditing.type=arg1;
}

void Create_in_Page::on_textEdit_textChanged()
{
    NowEditing.note=ui->textEdit->toPlainText();
}

