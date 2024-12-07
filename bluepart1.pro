QT       += core gui
QT       += charts
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BookKeeping2.cpp \
    accountpage.cpp \
    badget.cpp \
    badget_reminder.cpp \
    create_in_page.cpp \
    create_out_page.cpp \
    createpage.cpp \
    loginpage.cpp \
    main.cpp \
    set_badget.cpp \
    showpage.cpp

HEADERS += \
    BookKeeping2.h \
    accountpage.h \
    badget.h \
    badget_reminder.h \
    create_in_page.h \
    create_out_page.h \
    createpage.h \
    loginpage.h \
    set_badget.h \
    showpage.h

FORMS += \
    BookKeeping2.ui \
    accountpage.ui \
    badget.ui \
    badget_reminder.ui \
    create_in_page.ui \
    create_out_page.ui \
    createpage.ui \
    loginpage.ui \
    set_badget.ui \
    showpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    hahaha.qrc \
    touxiang.qrc
