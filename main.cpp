#include <QtGui/QApplication>
#include "mainwindow.h"
#include <getopt.h>
#include <QDebug>

static const char *optString = "t:rl";

static const struct option longOpts[] = {
    { "test", required_argument, NULL, 't' },
    { "autorun", no_argument, NULL, 'r' },
    { "autoload", no_argument, NULL, 'l' },
    { NULL, no_argument, NULL, 0 }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QString program;

    int longIndex;
    int opt = getopt_long( argc, argv, optString, longOpts, &longIndex );
    while( opt != -1 ) {
        switch( opt ) {
            case 't':
                qDebug() << "-t" << optarg;
                program = optarg;
                break;
            case 'r':
                qDebug() << "-r";
                break;
            case 'l':
                qDebug() << "-l";
                break;
            default:
                /* You won't actually get here. */
                qDebug() << optarg;
                break;
        }

        opt = getopt_long( argc, argv, optString, longOpts, &longIndex);
    }
    w.setFileName(program);
    w.getFunList();
    w.show();

    return a.exec();
}
