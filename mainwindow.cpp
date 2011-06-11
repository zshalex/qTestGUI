#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QDebug>

#include "optiondialog.h"
#include "aboutdialog.h"

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

    this->connect(ui->treeWidget,SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),this,SLOT(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)));
    this->connect(&_process,SIGNAL(testFinished(QString)),this,SLOT(runTestFinished(QString)));
    this->connect(&_process,SIGNAL(getFunListFinished(QStringList)),this,SLOT(getFunListFinished(QStringList)));

    this->connect(ui->actionRun,SIGNAL(triggered()),this,SLOT(runTest()));
    this->connect(ui->actionLoadFunction,SIGNAL(triggered()),this,SLOT(getFunList()));
    this->connect(ui->actionSaveAs,SIGNAL(triggered()),this,SLOT(save()));
    this->connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(open()));
    this->connect(ui->actionSelectFail,SIGNAL(triggered()),this,SLOT(selectFail()));
    this->connect(ui->actionSelectSuccess,SIGNAL(triggered()),this,SLOT(selectSuccess()));
    this->connect(ui->actionSelectAll,SIGNAL(triggered()),this,SLOT(selectAll()));
    this->connect(ui->actionUnselectAll,SIGNAL(triggered()),this,SLOT(unselectAll()));
    this->connect(ui->actionOption,SIGNAL(triggered()),this,SLOT(option()));
    this->connect(ui->actionAbaut,SIGNAL(triggered()),this,SLOT(about()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setConfig(Config *value)
{
    _config = value;
    if (_config != NULL) {
        changeTestFile(_config->testFile());
    }
}

void MainWindow::getFunList()
{
    if (QFile::exists(_process.testFile())) {
        if (_treeRoot != NULL) {
            clearTestCase();
            ui->progressBar->setValue(0);
            _process.getFunList();
        }
    }
}

void MainWindow::getFunListFinished(const QStringList &result)
{
    if (_treeRoot == NULL)
        return;

    _testManager.initFromFunctions(result);
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

    clearTestInfo();
    ui->tableWidget->item(0,0)->setText(QString::number(_testManager.count()));
    ui->statusBar->showMessage(tr("Load TestCase"));

    if (_config->autoRun()) {
        runTest();
    }
}

void MainWindow::runTest()
{
    if (QFile::exists(_process.testFile())) {
        if (_testManager.count() == 0)
            return;
        ui->progressBar->setValue(0);
        int checkCount = 0;
        for (int i = 0; i < _testManager.count(); i++) {
            _testManager.testCase(i)->setExecuted(false);
            if (_treeRoot->child(i)->checkState(0) == Qt::Checked) {
                _testManager.testCase(i)->setChecked(true);
                checkCount++;
            } else {
                _testManager.testCase(i)->setChecked(false);
            }
            _treeRoot->child(i)->setIcon(0,QIcon(":/image/normal.png"));
        }
        if (checkCount > 0) {
            ui->progressBar->setMaximum(checkCount);
        } else {
            ui->progressBar->setMaximum(100);
            return;
        }
        this->statusBar()->showMessage(tr("qTest is running"));
        _process.runTest(_testManager);
    }
}

void MainWindow::runTestFinished(const QString &result)
{
    _testManager.setTestResult(result);
    showResult();
    this->statusBar()->showMessage(tr("qTest has completed"));
}

void MainWindow::showResult()
{
    if (_treeRoot == NULL)
        return;

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

    QString qss = "QProgressBar {border: 2px solid grey;border-radius: 5px;text-align: center;}";;
    if (errorCount != 0) {
        qss += ("QProgressBar::chunk {background-color: #ff00ff;width: 10px;margin: 0.5px;}");
    } else {
        qss += ("QProgressBar::chunk {background-color: #00ff00;width: 10px;margin: 0.5px;}");
    }
    ui->progressBar->setStyleSheet(qss);
    ui->progressBar->setMaximum(sucCount + errorCount);
    ui->progressBar->setValue(sucCount);
}

void MainWindow::currentItemChanged(QTreeWidgetItem * current, QTreeWidgetItem *)
{
    if (current != NULL && current != _treeRoot) {
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

void MainWindow::save()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save test result"),"",tr("XML File(*.xml)"));
    if (!fileName.isEmpty()) {
        _testManager.saveResult(fileName);
    }
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open qTest file"),"",tr("Executable File(*.*)"));
    if (!fileName.isEmpty()) {
        changeTestFile(fileName);
    }
}

void MainWindow::selectFail()
{
    if (_treeRoot == NULL)
        return;

    TestCase *test;
    QTreeWidgetItem *item;
    for (int i = 0; i < _testManager.count(); i++) {
        test = _testManager.testCase(i);
        item = _treeRoot->child(i);

        if (test->result()){
            test->setChecked(false);
            item->setCheckState(0,Qt::Unchecked);
        } else {
            test->setChecked(true);
            item->setCheckState(0,Qt::Checked);
        }
    }
}

void MainWindow::selectSuccess()
{
    if (_treeRoot == NULL)
        return;

    TestCase *test;
    QTreeWidgetItem *item;
    for (int i = 0; i < _testManager.count(); i++) {
        test = _testManager.testCase(i);
        item = _treeRoot->child(i);

        if (test->result()){
            test->setChecked(true);
            item->setCheckState(0,Qt::Checked);
        } else {
            test->setChecked(false);
            item->setCheckState(0,Qt::Unchecked);
        }
    }
}

void MainWindow::selectAll()
{
    if (_treeRoot == NULL)
        return;

    TestCase *test;
    QTreeWidgetItem *item;
    for (int i = 0; i < _testManager.count(); i++) {
        test = _testManager.testCase(i);
        item = _treeRoot->child(i);
        test->setChecked(true);
        item->setCheckState(0,Qt::Checked);
    }
}

void MainWindow::unselectAll()
{
    if (_treeRoot == NULL)
        return;

    TestCase *test;
    QTreeWidgetItem *item;
    for (int i = 0; i < _testManager.count(); i++) {
        test = _testManager.testCase(i);
        item = _treeRoot->child(i);
        test->setChecked(false);
        item->setCheckState(0,Qt::Unchecked);
    }
}

void MainWindow::option()
{
    OptionDialog dialog;
    dialog.exec();
}

void MainWindow::about()
{
    AboutDialog dialog;
    dialog.exec();
}

void MainWindow::clearTestCase()
{
    if (_treeRoot != NULL) {
        while(_treeRoot->childCount() > 0) {
            _treeRoot->removeChild(_treeRoot->child(0));
        }
    }
}

void MainWindow::clearTestInfo()
{
    for(int i = 0; i < ui->tableWidget->columnCount(); i++){
        ui->tableWidget->item(0,i)->setText("");
    }
}

void MainWindow::changeTestFile(const QString &value)
{
    _process.setTestFile(value);
    ui->treeWidget->clear();
    _treeRoot = new QTreeWidgetItem(ui->treeWidget->invisibleRootItem());
    QFileInfo info(_process.testFile());
    _treeRoot->setText(0,info.fileName());
    clearTestInfo();
    if (_config->autoLoad()) {
        getFunList();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMainWindow::closeEvent(event);
    _config->saveToFile("./config.xml");
}
