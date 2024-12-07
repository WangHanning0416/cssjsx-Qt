#ifndef CREATE_IN_PAGE_H
#define CREATE_IN_PAGE_H

#include <QWidget>

namespace Ui {
class Create_in_Page;
}

class Create_in_Page : public QWidget
{
    Q_OBJECT
signals:
    void back();
    void saved();
public:
    explicit Create_in_Page(QWidget *parent = nullptr);
    ~Create_in_Page();

private slots:
    void on_pushButton_save_clicked();

    void on_pushButton_cancel_clicked();

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_textEdit_textChanged();

private:
    Ui::Create_in_Page *ui;
};

#endif // CREATE_IN_PAGE_H
