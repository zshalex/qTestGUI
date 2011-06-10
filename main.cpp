#include <QtGui/QApplication>
#include <getopt.h>

#include "mainwindow.h"
#include "config.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
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
