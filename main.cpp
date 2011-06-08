#include <QtGui/QApplication>
#include <QDebug>
#include <QProcess>
#include "unitgui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UnitGui w;
    QString program;
    for (int i = 0; i < argc; i++) {
        if (i == 1)
            program = argv[i];
    }
    w.setFileName(program);
    w.getFunList();
    w.show();

    return a.exec();
}
