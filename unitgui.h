#ifndef UNITGUI_H
#define UNITGUI_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "testprocess.h"
#include "testmanager.h"

namespace Ui {
    class UnitGui;
}

class UnitGui : public QDialog
{
    Q_OBJECT

public:
    explicit UnitGui(QWidget *parent = 0);
    ~UnitGui();

    void getFunList();

    const QString &fileName() const {return _fileName;}

    void setFileName(const QString &value);
private slots:
    void runTest();
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void openFile();
private:
    Ui::UnitGui *ui;

    QString _fileName;
    QStringList _arguments;
    TestProcess _process;
    TestManager _testManager;
    QTreeWidgetItem *treeRoot;

    void showResult(QByteArray array);
};

#endif // UNITGUI_H
