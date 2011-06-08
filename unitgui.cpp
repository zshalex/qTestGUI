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
}

UnitGui::~UnitGui()
{
    delete ui;
}

void UnitGui::setFileName(const QString &value)
{
    _fileName = value;
    _process.setTestFile(_fileName);
    ui->labFileName->setText(value);
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
        for (int i = 0; i < _testManager.count(); i++) {
            QTreeWidgetItem *treeItem = new QTreeWidgetItem(treeRoot);
            treeItem->setText(0,_testManager.testCase(i)->name());
            treeItem->setIcon(0,QIcon(":/image/normal.bmp"));
            if (_testManager.testCase(i)->checked())
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
        for (int i = 0; i < _testManager.count(); i++) {
            if (treeRoot->child(i)->checkState(0) == Qt::Checked)
                _testManager.testCase(i)->setChecked(true);
            else
                _testManager.testCase(i)->setChecked(false);
        }

        _testManager.setTestResult(_process.getTestResult(_testManager));
        showResult(NULL);
    }
}

void UnitGui::showResult(QByteArray array)
{
    for (int i = 0; i < _testManager.count(); i++) {
        if (_testManager.testCase(i)->checked()) {
            treeRoot->child(i)->setText(1,_testManager.testCase(i)->resultStr());
            if (_testManager.testCase(i)->result()) {
                treeRoot->child(i)->setIcon(0,QIcon(":/image/succ.bmp"));
            } else {
                treeRoot->child(i)->setIcon(0,QIcon(":/image/fail.bmp"));
                treeRoot->child(i)->setText(2,_testManager.testCase(i)->errorMessage());
            }
        } else {
            treeRoot->child(i)->setIcon(0,QIcon(":/image/normal.bmp"));
        }
    }
}
