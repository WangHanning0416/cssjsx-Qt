#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>
#include "BookKeeping2.h"

namespace Ui {
class LoginPage;
}
class MyMainPage;
class QErrorMessage;
class LoginPage : public QWidget
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr);
    ~LoginPage();
    Widget *mainpage = NULL;
    QErrorMessage *errordlg;
    void judgelogin();

private slots:
    void on_pushButton_clicked();

private:
    Ui::LoginPage *ui;
};

#endif // LOGINPAGE_H
