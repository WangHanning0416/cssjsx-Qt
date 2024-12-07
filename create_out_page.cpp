#include <QDate>
#include "create_out_page.h"
#include "badget.h"
#include "BookKeeping2.h"
#include "ui_create_out_page.h"
//item NowEditing;
Create_out_Page::Create_out_Page(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Create_out_Page)
{
    ui->setupUi(this);
    this->reminder = new badget_reminder;
}

Create_out_Page::~Create_out_Page()
{
    delete ui;
}

void Create_out_Page::on_pushButton_save_clicked()
{
    int m=0,y=0,d=0;
    QDate::currentDate().getDate(&y,&m,&d);

    NowEditing.date=d;
    NowEditing.month=m;
    NowEditing.in_out=1;
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
    Days[Day_id].day_out+=NowEditing.money;
    badgets[NowEditing.type].get_rest_of_month(m)-=NowEditing.money;
    total_out+=NowEditing.money;
    pure=total_in-total_out;
    db.deleteAllData();
    for (int i = 0; i <= 92; i++) {
        db.insertData(Days[i]);
    }
    update();
    emit this->saved();
    //emit this->back();
    if(badgets[NowEditing.type].get_rest_of_month(m)<0)
        this->reminder->show();
    this->close();
}


void Create_out_Page::on_pushButton_cancel_clicked()
{
    emit this->back();
}


void Create_out_Page::on_doubleSpinBox_valueChanged(double arg1)
{
    NowEditing.money=arg1;
}


void Create_out_Page::on_comboBox_currentTextChanged(const QString &arg1)
{
    NowEditing.type=arg1;
}


void Create_out_Page::on_textEdit_textChanged()
{
    NowEditing.note=ui->textEdit->toPlainText();
}
