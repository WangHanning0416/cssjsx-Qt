#include <QApplication>
#include "loginpage.h"
#include "BookKeeping2.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginPage w;
    w.show();
    return a.exec();
}
