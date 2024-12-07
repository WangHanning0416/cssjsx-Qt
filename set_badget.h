#ifndef SET_BADGET_H
#define SET_BADGET_H

#include <QWidget>

namespace Ui {
class set_badget;
}

class set_badget : public QWidget
{
    Q_OBJECT
signals:
    void back();
public:
    explicit set_badget(QWidget *parent = nullptr);
    ~set_badget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_input_valueChanged(double arg1);

    void on_type_currentTextChanged(const QString &arg1);

private:
    Ui::set_badget *ui;
};

#endif // SET_BADGET_H
