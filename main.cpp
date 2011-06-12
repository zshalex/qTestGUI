#include <QtGui/QApplication>
#include <getopt.h>
#include <QDebug>

#include "mainwindow.h"
#include "config.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationVersion("1.0");
    a.setApplicationName("qTestGUI");
    qDebug() << a.applicationName() << a.applicationVersion();
    //load config and arg
    Config config;
    config.setAppPath(QApplication::applicationDirPath());
    config.loadFromFile("./config.xml");
    config.loadFromArg(argc,argv);
    //run MainWindow
    MainWindow w;
    w.setConfig(&config);
    w.show();
    return a.exec();
}
