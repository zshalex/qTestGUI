#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

///Ui命名空间
namespace Ui {
    class AboutDialog;
}

///关于对话框
/**
  关于对话框,其中包括软件名,作者,版本
  @author Alex Zhao
  @version 1.0
  */

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    ///构造函数
    /**
      @param parent 当前类的parent
      @see ~AboutDialog()
      */
    AboutDialog(QWidget *parent = 0);
    ///析构函数
    /**
      @see AboutDialog()
      */
    ~AboutDialog();

private:
    ///ui类
    Ui::AboutDialog *ui;
};

#endif // ABOUTDIALOG_H
