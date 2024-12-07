#ifndef CREATE_OUT_PAGE_H
#define CREATE_OUT_PAGE_H

#include <QWidget>
#include "badget_reminder.h"

namespace Ui {
class Create_out_Page;
}

class badget_reminder;
class Create_out_Page : public QWidget
{
    Q_OBJECT
signals:
    void back();
    void saved();
public:
    explicit Create_out_Page(QWidget *parent = nullptr);
    ~Create_out_Page();
    badget_reminder *reminder=NULL;

private slots:
    void on_pushButton_save_clicked();

    void on_pushButton_cancel_clicked();

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_textEdit_textChanged();

private:
    Ui::Create_out_Page *ui;
};

#endif // CREATE_OUT_PAGE_H
