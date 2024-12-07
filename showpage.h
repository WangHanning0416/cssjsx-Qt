#ifndef SHOWPAGE_H
#define SHOWPAGE_H

#include <QWidget>

namespace Ui {
class ShowPage;
}

class ShowPage : public QWidget
{
    Q_OBJECT

public:
    explicit ShowPage(QWidget *parent = nullptr);
    ~ShowPage();
signals:
    void back();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ShowPage *ui;
};

#endif // SHOWPAGE_H
