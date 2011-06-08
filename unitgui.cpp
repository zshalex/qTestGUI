#include "unitgui.h"
#include "ui_unitgui.h"
#include <QStringList>
#include <QDebug>
#include <QTreeWidgetItem>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>

UnitGui::UnitGui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UnitGui)
{
    ui->setupUi(this);

    this->connect(ui->btnRun,SIGNAL(clicked()),this,SLOT(runTest()));
//    this->connect(this->_process,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(processFinished(int,QProcess::ExitStatus)));
    this->connect(ui->btnBrowser,SIGNAL(clicked()),this,SLOT(openFile()));
}

UnitGui::~UnitGui()
{
    delete ui;
}

void UnitGui::setFileName(const QString &value)
{
    _fileName = value;
    _process.setTestFile(_fileName);
    ui->edFileName->setText(_fileName);
//    runTest();
}

void UnitGui::getFunList()
{
    if (QFile::exists(_fileName)) {
        _testManager.initFromFunctions(_process.getFunList());
        ui->treeWidget->clear();
        treeRoot = new QTreeWidgetItem(ui->treeWidget->invisibleRootItem());
        QFileInfo info(_fileName);
        treeRoot->setText(0,info.baseName());
        for (int i = 0; i < _testManager.length(); i++) {
            QTreeWidgetItem *treeItem = new QTreeWidgetItem(treeRoot);
            treeItem->setText(0,_testManager.at(i).name());
            treeItem->setIcon(0,QIcon());
            if (_testManager.at(i).checked())
                treeItem->setCheckState(0,Qt::Checked);
            else
                treeItem->setCheckState(0,Qt::Unchecked);
        }
        treeRoot->setExpanded(true);
    }
}

void UnitGui::runTest()
{
    if (QFile::exists(_fileName)) {
        ui->btnRun->setEnabled(false);
        ui->btnClear->setEnabled(false);

        for (int i = 0; i < _testManager.length(); i++) {
            if (treeRoot->child(i)->checkState(0) == Qt::Checked)
                _testManager[i].setChecked(true);
            else
                _testManager[i].setChecked(false);
        }

        _testManager.setTestResult(_process.getTestResult(_testManager));
        showResult(NULL);
    }
}

void UnitGui::showResult(QByteArray array)
{
    for (int i = 0; i < _testManager.length(); i++) {
        if (_testManager.at(i).checked()) {
            treeRoot->child(i)->setText(1,_testManager.at(i).resultStr());
            if (_testManager.at(i).result()) {
                treeRoot->child(i)->setIcon(0,QIcon(":/image/succ.bmp"));
            } else {
                treeRoot->child(i)->setIcon(0,QIcon(":/image/fail.bmp"));
                treeRoot->child(i)->setText(2,_testManager.at(i).errorMessage());
            }
        } else {
            treeRoot->child(i)->setIcon(0,QIcon());
        }
    }
}

void UnitGui::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    ui->btnRun->setEnabled(true);
    ui->btnClear->setEnabled(true);
    setWindowTitle("qTestGUI - Testing has completed");
}

void UnitGui::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                tr("Open qTest Program"), "/");
    setFileName(fileName);
}
