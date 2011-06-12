#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    ui->labAppVersion->setText(QApplication::applicationName());
    ui->labAppVersion->setText(QApplication::applicationVersion());
    ui->labAppAuthor->setText("Alex Zhao");
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
