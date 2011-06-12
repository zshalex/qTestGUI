#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>

#include "testprocess.h"
#include "testmanager.h"
#include "config.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setConfig(Config *value);
public slots:
    void getFunList();
    void runTest();
    void save();
    void open();
    void selectAll();
    void unselectAll();
    void selectFail();
    void selectSuccess();
    void option();
    void about();
    void autoRun(const bool &value);
    void autoLoad(const bool &value);
private slots:
    void currentItemChanged(QTreeWidgetItem * current, QTreeWidgetItem * previous);
    void runTestFinished(const QString &result);
    void getFunListFinished(const QStringList &result);
private:
    void showResult();
    void clearTestCase();
    void clearTestInfo();
    void changeTestFile(const QString &value);
    void closeEvent(QCloseEvent *event);
private:
    Ui::MainWindow *ui;
    TestProcess _process;
    TestManager _testManager;
    QTreeWidgetItem *_treeRoot;
    Config *_config;
};

#endif // MAINWINDOW_H
