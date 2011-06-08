#-------------------------------------------------
#
# Project created by QtCreator 2011-06-07T14:09:18
#
#-------------------------------------------------

QT       += core gui xml

TARGET = qTestGUI
TEMPLATE = app


SOURCES += main.cpp\
        unitgui.cpp \
    testcase.cpp \
    testmanager.cpp \
    testprocess.cpp

HEADERS  += unitgui.h \
    testcase.h \
    testmanager.h \
    testprocess.h

FORMS    += unitgui.ui

RESOURCES += \
    res.qrc
