#ifndef MYMAINPAGE_H
#define MYMAINPAGE_H

#include <QWidget>
#include "createpage.h"
#include "showpage.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MyMainPage;
}
QT_END_NAMESPACE


class CreatePage;
class ShowPage;
class MyMainPage : public QWidget
{
    Q_OBJECT

public:
    MyMainPage(QWidget *parent = nullptr);
    ~MyMainPage();
    CreatePage *createpage = NULL;
    ShowPage *showpage = NULL;
private slots:
    void on_pushButton_clicked();
    void comeback1();
    void comeback2();

    void on_pushButton_2_clicked();

private:
    Ui::MyMainPage *ui;
};
#endif // MYMAINPAGE_H
