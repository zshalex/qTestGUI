#-------------------------------------------------
#
# Project created by QtCreator 2011-06-07T14:09:18
#
#-------------------------------------------------

QT       += core gui xml

TARGET = qTestGUI
TEMPLATE = app


SOURCES += main.cpp\
    testcase.cpp \
    testmanager.cpp \
    testprocess.cpp \
    mainwindow.cpp \
    optiondialog.cpp

HEADERS  += testcase.h \
    testmanager.h \
    testprocess.h \
    mainwindow.h \
    optiondialog.h

FORMS    += mainwindow.ui \
    optiondialog.ui

RESOURCES += \
    res.qrc
win32 {
    OTHER_FILES += \
        app.rc
    #Setting the Application Icon
    RC_FILE = app.rc
}
macx{
    ICON = ./image/app.icns
}
