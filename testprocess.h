///执行单元测试的类
/**
  使用QProcess类调用单元测试,其中主要功能是获取单元测试列表,
  以及单元测试的结果.
  @author Alex Zhao
  @version 1.0
  */

#ifndef TESTPROCESS_H
#define TESTPROCESS_H

#include <QObject>
#include <QProcess>
#include <QString>
#include <QStringList>
#include "testmanager.h"

class TestProcess : public QObject
{
    Q_OBJECT
public:
    ///执行单元测试的子功能
    /**
      <p>
      通过不同的参数,获取单元测试中不同的信息.
      </p>
      <p>
      例如:使用-functions参数,会返回测试用例列表.
          使用-xml参数,会以xml格式返回测试结果.
      </p>
      @see _curTask
      */
    typedef enum {
        GetFunList = 0, /**< 返回测试用例列表 */
        RunTest = 1 /**< 返回测试结果 */
    } TaskName;

    ///构造函数
    /**
      @param parent 当前类的parent
      @see ~TestProcess()
      */
    TestProcess(QObject *parent = 0);
    ///析构函数
    /**
      @see TestProcess()
      */
    ~TestProcess();

    ///获取测试用例列表
    /**
      调用单元测试程序,并使用-functions参数返回测试用例列表.
      执行完成后,会触发getFunListFinished(const QStringList &result)
      信号.
      @return 执行成功返回true,否则返回false
      @see getFunListFinished()
      */
    bool getFunList();
    ///获取单元测试结果
    /**
      调用单元测试程序,并使用-xml参数,并运行testManager中选中的测试用例.
      执行完成后,会触发testFinished(const QString &result)
      信号.
      @param testManager 单元测试的管理类
      @return 执行成功返回true,否则返回false
      @see testFinished()
      @see TestManager
      */
    bool runTest(TestManager &testManager);
    ///获取单元测试程序的文件名
    /**
      @return 单元测试程序的文件名
      @see setTestFile()
      */
    const QString &testFile() {return _testFile;}
    ///设置单元测试程序的文件名
    /**
      @param value 单元测试程序的文件名
      @see testFile()
      */
    void setTestFile(const QString &value);
signals:
    ///执行单元测试结束时触发的信号
    /**
      @param result 单元测试执行的结果
      @see runTest()
      */
    void testFinished(const QString &result);
    ///获取测试用例列表后触发的信号
    /**
      @param result 测试用例列表
      @see getFunList()
      */
    void getFunListFinished(const QStringList &result);
private slots:
    ///进程运行结束时执行的槽
    /**
      @param exitCode 进程的返回值
      @see _process
      */
    void processFinished(int exitCode);
private:
    ///根据testManager中的测试用例信息,返回执行单元测试时使用的参数值.
    /**
      @param testManager 单元测试信息
      @return 返回testManager中,用户选中的测试用例(checked() == true)列表.
      */
    QStringList getArgs(TestManager &testManager);
private:
    ///进程类,用于执行单元测试程序.
    /**
      @see processFinished()
      */
    QProcess *_process;
    ///单元测试程序的文件名
    /**
      @see testFile()
      @see setTestFile()
      */
    QString _testFile;
    ///单元测试的子功能类型
    /**
      @see TaskName
      */
    TaskName _curTask;
};

#endif // TESTPROCESS_H
