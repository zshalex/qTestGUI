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

    void getFunList();
    void setFileName(const QString &value);
public slots:
    void runTest();
private slots:
    void currentItemChanged(QTreeWidgetItem * current, QTreeWidgetItem * previous);
private:
    void showResult();
private:
    Ui::MainWindow *ui;
    TestProcess _process;
    TestManager _testManager;
    QTreeWidgetItem *_treeRoot;
};

#endif // MAINWINDOW_H
