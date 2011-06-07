#include "unitgui.h"
#include "ui_unitgui.h"
#include <QStringList>
#include <QDebug>
#include <QTreeWidgetItem>
#include <QFile>

UnitGui::UnitGui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UnitGui)
{
    ui->setupUi(this);

    _process = new QProcess(this);

//    ui->treeView->setCol

    this->connect(ui->btnRun,SIGNAL(clicked()),this,SLOT(runTest()));
    this->connect(this->_process,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(processFinished(int,QProcess::ExitStatus)));
}

UnitGui::~UnitGui()
{
    delete _process;
    delete ui;
}

void UnitGui::setFileName(const QString &value)
{
    _fileName = value;
    ui->lineEdit->setText(_fileName);
    runTest();
}

void UnitGui::runTest()
{
    if (QFile::exists(_fileName)) {
        _process->start(_fileName,_arguments);
        ui->treeWidget->clear();
        ui->btnRun->setEnabled(false);
        ui->btnClear->setEnabled(false);
        this->setWindowTitle("qTestGUI - Testing is running");
    }
}

void UnitGui::showResult(QByteArray array)
{    
    QString str(array);
    QStringList list = str.split('\n');
    QString res;
    QString obj;
    QString med;
    QString error;
    QString des;
    int index;
    for (int i = 0; i < list.length(); i++){
        list[i] = list.at(i).trimmed();
        res = "";
        QStringList tmpList;
        if (list.at(i).startsWith(QString("PASS")) || list.at(i).startsWith(QString("FAIL"))) {
            tmpList = list.at(i).split(":");

            res = tmpList.at(0).trimmed();
            obj = tmpList.at(1).trimmed();
            des = tmpList.at(3).trimmed();
            med = des;
            index = med.indexOf('(');
            if (index != -1)
                med.resize(index);

            QList<QTreeWidgetItem *> iList = ui->treeWidget->findItems(obj,Qt::MatchExactly);
            QTreeWidgetItem *treeItem;

            if (iList.length() > 0) {
                treeItem = iList.at(0);
            } else {
                treeItem = new QTreeWidgetItem(ui->treeWidget->invisibleRootItem());
                treeItem->setText(0,obj);
            }
            treeItem->setExpanded(true);
            QTreeWidgetItem *item = new QTreeWidgetItem(treeItem);
            if (res.startsWith("PASS")) {
                item->setIcon(0,QIcon(":/image/succ.bmp"));
            } else {
                item->setIcon(0,QIcon(":/image/fail.bmp"));
                index = des.indexOf(')');
                error = des.mid(index + 1).trimmed();
                item->setText(2,error);
            }
            item->setText(0,med);
            item->setText(1,res);
        }
    }
}

void UnitGui::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    showResult(_process->readAll());
    ui->btnRun->setEnabled(true);
    ui->btnClear->setEnabled(true);
    setWindowTitle("qTestGUI - Testing has completed");

}
