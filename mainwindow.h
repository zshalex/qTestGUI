#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include "testprocess.h"
#include "testmanager.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setFileName(const QString &value);
public slots:
    void getFunList();
    void runTest();
    void save();
    void open();
    void selectAll();
    void unselectAll();
    void selectFail();
    void selectSuccess();
private slots:
    void currentItemChanged(QTreeWidgetItem * current, QTreeWidgetItem * previous);
    void runTestFinished(const QString &result);
    void getFunListFinished(const QStringList &result);
private:
    void showResult();
private:
    Ui::MainWindow *ui;
    TestProcess _process;
    TestManager _testManager;
    QTreeWidgetItem *_treeRoot;
};

#endif // MAINWINDOW_H
