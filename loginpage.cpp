#include "loginpage.h"
#include "ui_loginpage.h"
#include "BookKeeping2.h"
#include <QErrorMessage>
LoginPage::LoginPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginPage)
{
    ui->setupUi(this);
    this->mainpage = new Widget;
}

LoginPage::~LoginPage()
{
    delete ui;
}

void LoginPage::judgelogin() {
    QString nameString = ui->username->text();
    QString passwordString = ui->password->text();
    if (nameString != "odui123") {
        errordlg = new QErrorMessage(this);
        errordlg->setWindowTitle(tr("错误"));
        errordlg->showMessage((tr("用户名不存在")));
        errordlg->show();
    }
    else if (passwordString != "123456") {
        errordlg = new QErrorMessage(this);
        errordlg->setWindowTitle(tr("错误"));
        errordlg->showMessage((tr("密码错误")));
    }
    else {
        this->close();
        this->mainpage->show();
    }
}

void LoginPage::on_pushButton_clicked()
{
    this->judgelogin();
}

