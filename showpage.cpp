#include "showpage.h"
#include "ui_showpage.h"

ShowPage::ShowPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ShowPage)
{
    ui->setupUi(this);
}

ShowPage::~ShowPage()
{
    delete ui;
}

void ShowPage::on_pushButton_clicked()
{
    emit back();
}

