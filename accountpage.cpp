#include "accountpage.h"
#include "ui_accountpage.h"

AccountPage::AccountPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AccountPage)
{
    ui->setupUi(this);
}

AccountPage::~AccountPage()
{
    delete ui;
}

void AccountPage::on_pushButton_clicked()
{

}

