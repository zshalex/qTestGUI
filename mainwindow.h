#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>

#include "testprocess.h"
#include "testmanager.h"
#include "config.h"

namespace Ui {
    class MainWindow;
}

///主窗体
/**
  显示 & 控制单元测试
  @author Alex Zhao
  @date 2011-7-15
  @version 1.0
  */

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    ///构造函数
    /**
      @param parent 当前类的parent
      @see ~MainWindow()
      */
    MainWindow(QWidget *parent = 0);
    ///析构函数
    /**
      @see MainWindow()
      */
    ~MainWindow();

    ///设置配置信息
    /**
      @param value 配置信息
      */
    void setConfig(Config *value);
public slots:
    ///获取测试用例列表
    void getFunList();
    ///运行单元测试
    void runTest();
    ///保存测试结果
    void save();
    ///打开单元测试
    void open();
    ///选中所有测试用例
    void selectAll();
    ///不选中所有测试用例
    void unselectAll();
    ///只选策测试失败的测试用例
    void selectFail();
    ///只选择测试成功的测试用例
    void selectSuccess();
    ///显示参数配置对话框(暂时不使用)
    void option();
    ///显示关于对话框
    void about();
    ///设置自动运行参数
    /**
      @param value 自动运行
      */
    void autoRun(const bool &value);
    ///设置自动导入参数
    /**
      @param value 自动导入
      */
    void autoLoad(const bool &value);
private slots:
    ///QTreeWidget的currentItemChanged信号对应的槽'
    /**
      切换测试用例时触发,用于显示测试用例的信息.
      @param current 当前选中的项
      @param previous 之前选中的项
      */
    void currentItemChanged(QTreeWidgetItem * current, QTreeWidgetItem * previous);
    ///测试运行完成时触发的槽
    /**
      @param result 测试结果
      */
    void runTestFinished(const QString &result);
    ///获取测试用例列表后触发的槽
    /**
      @param result 测试用例列表
      */
    void getFunListFinished(const QStringList &result);
private:
    ///显示测试结果
    void showResult();
    ///清空测试用例
    void clearTestCase();
    ///清空测试用例信息
    void clearTestInfo();
    ///切换单元测试程序
    /**
      @param value 单元测试程序的文件名
      */
    void changeTestFile(const QString &value);
    ///关闭事件
    /**
      @param event 事件对象
      */
    void closeEvent(QCloseEvent *event);
private:
    ///ui对象
    Ui::MainWindow *ui;
    ///执行测试用例的对象
    TestProcess _process;
    ///管理测试用例的对象
    TestManager _testManager;
    ///QTreeWidget的根节点
    QTreeWidgetItem *_treeRoot;
    ///配置信息
    Config *_config;
};

#endif // MAINWINDOW_H
