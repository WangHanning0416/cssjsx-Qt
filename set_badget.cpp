#include "set_badget.h"
#include "ui_set_badget.h"
#include "badget.h"
#include <QDate>

set_badget::set_badget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::set_badget)
{
    ui->setupUi(this);
    int y=0,m=0,d=0;
    QDate::currentDate().getDate(&y,&m,&d);
    ui->sancan->setNum(badgets["三餐"].get_rest_of_month(m));
    ui->lingshi->setNum(badgets["零食"].get_rest_of_month(m));
    ui->yifu->setNum(badgets["衣服"].get_rest_of_month(m));
    ui->jiaotong->setNum(badgets["交通"].get_rest_of_month(m));
    ui->riyongpin->setNum(badgets["日用品"].get_rest_of_month(m));
    ui->yiliao->setNum(badgets["医疗"].get_rest_of_month(m));
    ui->xuexi->setNum(badgets["学习"].get_rest_of_month(m));
    ui->yule->setNum(badgets["娱乐"].get_rest_of_month(m));
    ui->qita->setNum(badgets["其他"].get_rest_of_month(m));
}

set_badget::~set_badget()
{
    delete ui;
}

void set_badget::on_pushButton_clicked()//保存按钮
{
    Badget& badget=badgets[editing_type];
    double tmp=editing_badget-badget.get_total_badget();
    badget.get_total_badget()=editing_badget;
    for(int i=5;i<8;i++)
        badget.get_rest_of_month(i)+=tmp;
    this->hide();
}


void set_badget::on_pushButton_2_clicked()//取消按钮
{
    this->hide();
}


void set_badget::on_input_valueChanged(double arg1)
{
    editing_badget=arg1;
}


void set_badget::on_type_currentTextChanged(const QString &arg1)
{
    editing_type=arg1;
    ui->input->setValue(badgets[arg1].get_total_badget());
}

