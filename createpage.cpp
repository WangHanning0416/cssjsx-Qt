#include "createpage.h"
#include "ui_createpage.h"

CreatePage::CreatePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CreatePage)
{
    ui->setupUi(this);
    this->inpage = new Create_in_Page;
    connect(this->inpage, SIGNAL(back()), this, SLOT(comeback_in()));
    connect(this->inpage, SIGNAL(saved()), this, SLOT(closeit()));
    this->outpage = new Create_out_Page;
    connect(this->outpage, SIGNAL(back()), this, SLOT(comeback_out()));
    connect(this->outpage, SIGNAL(saved()), this, SLOT(closeit()));

}

CreatePage::~CreatePage()
{
    delete ui;
}

void CreatePage::on_pushButton_clicked()
{
    this->close();
}


void CreatePage::on_pushButton_in_clicked()
{
    this->hide();
    this->inpage->show();
}

void CreatePage::comeback_in() {
    this->inpage->hide();
    this->show();
}
void CreatePage::on_pushButton_out_clicked()
{
    this->hide();
    this->outpage->show();
}

void CreatePage::comeback_out() {
    this->outpage->hide();
    this->show();
}
void CreatePage::closeit() {
    this->hide();
}
