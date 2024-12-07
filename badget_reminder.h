#ifndef BADGET_REMINDER_H
#define BADGET_REMINDER_H

#include <QWidget>

namespace Ui {
class badget_reminder;
}

class badget_reminder : public QWidget
{
    Q_OBJECT
signals:
    void back();
public:
    explicit badget_reminder(QWidget *parent = nullptr);
    ~badget_reminder();

private slots:
    void on_pushButton_clicked();

private:
    Ui::badget_reminder *ui;
};

#endif // BADGET_REMINDER_H
