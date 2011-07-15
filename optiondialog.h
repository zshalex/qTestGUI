#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include <QDialog>

namespace Ui {
    class OptionDialog;
}

///参数配置对话框
/**
  暂时未使用
  */

class OptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionDialog(QWidget *parent = 0);
    ~OptionDialog();

private:
    Ui::OptionDialog *ui;
};

#endif // OPTIONDIALOG_H
