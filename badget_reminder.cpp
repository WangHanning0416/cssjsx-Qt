#include "badget_reminder.h"
#include "ui_badget_reminder.h"
#include "badget.h"
#include <QDate>
badget_reminder::badget_reminder(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::badget_reminder)
{
    ui->setupUi(this);
}

badget_reminder::~badget_reminder()
{
    delete ui;
}

void badget_reminder::on_pushButton_clicked()
{
    this->hide();
}

