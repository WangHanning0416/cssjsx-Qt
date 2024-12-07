#include "mymainpage.h"
#include "ui_mymainpage.h"

MyMainPage::MyMainPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyMainPage)
{
    ui->setupUi(this);
    this->createpage = new CreatePage;
    connect(this->createpage, SIGNAL(back()), this, SLOT(comeback1()));
    this->showpage = new ShowPage;
    connect(this->showpage, SIGNAL(back()), this, SLOT(comeback2()));
}

MyMainPage::~MyMainPage()
{
    delete ui;
}

void MyMainPage::on_pushButton_clicked()
{
    this->close();
    this->createpage->show();
}

void MyMainPage::comeback1() {
    this->createpage->hide();
    this->show();
}
void MyMainPage::on_pushButton_2_clicked()
{
    this->close();
    this->showpage->show();
}
void MyMainPage::comeback2() {
    this->showpage->hide();
    this->show();
}

