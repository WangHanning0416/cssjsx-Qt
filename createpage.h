#ifndef CREATEPAGE_H
#define CREATEPAGE_H

#include <QWidget>
#include "create_in_page.h"
#include "create_out_page.h"
namespace Ui {
class CreatePage;
}

class Create_in_Page;
class Create_out_Page;
class CreatePage : public QWidget
{
    Q_OBJECT

public:
    explicit CreatePage(QWidget *parent = nullptr);
    ~CreatePage();
    Create_in_Page *inpage = NULL;
    Create_out_Page *outpage = NULL;

signals:
    void back();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_in_clicked();

    void on_pushButton_out_clicked();

    void comeback_in();
    void comeback_out();
    void closeit();
private:
    Ui::CreatePage *ui;
};

#endif // CREATEPAGE_H
