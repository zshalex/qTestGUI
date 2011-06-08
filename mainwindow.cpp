#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("qTestGUI");

    ui->tableWidget->insertRow(0);
    ui->tableWidget->setRowHeight(0,20);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    for(int i = 0; i < ui->tableWidget->columnCount(); i++){
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText("");
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(0,i,item);
    }

    this->connect(ui->actionRun,SIGNAL(triggered()),this,SLOT(runTest()));
    this->connect(ui->treeWidget,SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),this,SLOT(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getFunList()
{
    if (QFile::exists(_process.testFile())) {
        _testManager.initFromFunctions(_process.getFunList());
        ui->treeWidget->clear();
        _treeRoot = new QTreeWidgetItem(ui->treeWidget->invisibleRootItem());
        QFileInfo info(_process.testFile());
        _treeRoot->setText(0,info.fileName());
        for (int i = 0; i < _testManager.count(); i++) {
            QTreeWidgetItem *treeItem = new QTreeWidgetItem(_treeRoot);
            treeItem->setText(0,_testManager.testCase(i)->name());
            treeItem->setIcon(0,QIcon(":/image/normal.png"));
            _testManager.testCase(i)->setExecuted(false);
            if (_testManager.testCase(i)->checked())
                treeItem->setCheckState(0,Qt::Checked);
            else
                treeItem->setCheckState(0,Qt::Unchecked);
        }
        _treeRoot->setExpanded(true);

        ui->tableWidget->item(0,0)->setText(QString::number(_testManager.count()));
    }
}

void MainWindow::setFileName(const QString &value)
{
    _process.setTestFile(value);
}

void MainWindow::runTest()
{
    if (QFile::exists(_process.testFile())) {
        ui->progressBar->setValue(0);
        for (int i = 0; i < _testManager.count(); i++) {
            if (_treeRoot->child(i)->checkState(0) == Qt::Checked)
                _testManager.testCase(i)->setChecked(true);
            else
                _testManager.testCase(i)->setChecked(false);
        }

        _testManager.setTestResult(_process.getTestResult(_testManager));
        showResult();
    }
}

void MainWindow::showResult()
{
    int sucCount = 0;
    int errorCount = 0;
    for (int i = 0; i < _testManager.count(); i++) {
        if (_testManager.testCase(i)->checked()) {
            if (_testManager.testCase(i)->result()) {
                _treeRoot->child(i)->setIcon(0,QIcon(":/image/succ.png"));
                sucCount++;
            } else {
                _treeRoot->child(i)->setIcon(0,QIcon(":/image/fail.png"));
                errorCount++;
            }
        } else {
            _treeRoot->child(i)->setIcon(0,QIcon(":/image/normal.png"));
        }
    }
    ui->tableWidget->item(0,1)->setText(QString::number(sucCount + errorCount));
    ui->tableWidget->item(0,2)->setText(QString::number(sucCount));
    ui->tableWidget->item(0,3)->setText(QString::number(errorCount));
    ui->progressBar->setMaximum(sucCount + errorCount);
    ui->progressBar->setValue(sucCount);
}

void MainWindow::currentItemChanged(QTreeWidgetItem * current, QTreeWidgetItem * previous)
{
    if (current != _treeRoot) {
        int index = _testManager.indexOfByFunName(current->text(0));
        if (index == -1)
            return;
        TestCase *test = _testManager.testCase(index);
        ui->textEdit->clear();
        if (test->checked() && !test->result() && test->executed()) {
            QString errFile = QString().sprintf("Source File: %s",test->errorFile().toAscii().data());
            ui->textEdit->append(errFile);
            QString errLine = QString().sprintf("Error line number: %d",test->errorLine());
            ui->textEdit->append(errLine);
            ui->textEdit->append(test->errorMessage());

        }
    }
}
