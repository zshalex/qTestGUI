/// 测试用例的包装类
/**
  包含测试用例的基本信息,包括用例名,测试结构等.
  @author Alex Zhao
  @version 1.0
  */

#ifndef TESTCASE_H
#define TESTCASE_H

#include <QString>
#include <QStringList>

class TestCase
{
public:
    ///构造函数
    /**
      构造函数中初始化类成员变量.
      */
    TestCase();

    ///初始化用例的名称
    /**
      在Qt测试框架中,初始化用例的名称,当前值为"initTestCase".
      */
    const static QString INIT_TEST_CASE;
    ///清理用例的名称
    /**
      在Qt测试框架中,清理用例的名称,当前值为"cleanupTestCase".
      */
    const static QString CLEAN_TEST_CASE;

    ///获取用例名
    /**
      @return 用例名
      @see setName()
      */
    const QString &name() const {return _name;}
    ///获取测试结果
    /**
      @return 测试结果,测试成功返回"PASS",测试失败返回"FAIL"等
      @see setResultStr
      */
    const QString &resultStr() const {return _resultStr;}
    ///获取测试结果
    /**
      @return 测试结果,测试成功返回true,测试失败返回false
      @see setResult()
      */
    const bool &result() const {return _result;}
    ///获取错误信息
    /**
      @return 错误信息
      @see setErrorMessage()
      */
    const QString &errorMessage() const {return _errorMessage;}
    ///获取错误所在行号
    /**
      @return 错误所在行号
      @see setErrorLine()
      */
    const int &errorLine() const {return _errorLine;}
    ///获取错误所在文件
    /**
      @return 错误所在文件
      @see setErrorFile()
      */
    const QString &errorFile() const {return _errorFile;}
    ///获取测试用例是否已经执行
    /**
      @return 测试用例是否已经执行
      @see setExecuted()
      */
    const bool &executed() const {return _executed;}
    ///获取测试用例是否需要执行
    /**
      @return 测试用例是否需要执行
      @see setChecked()
      */
    const bool &checked() const {return _checked;}
    ///获取调试信息
    /**
      @return 调试信息
      @see setMessage()
      */
    QStringList &message() {return _message;}
    ///获取benchmark信息
    /**
      @return benchmark信息
      @see setBenchmark()
      */
    QStringList &benchmark() {return _benchmark;}

    ///设置测试用例名
    /**
      @param value 测试用例名
      @see name()
      */
    void setName(const QString &value);
    ///设置测试结果
    /**
      @param value 测试结果
      @see resultStr()
      */
    void setResultStr(const QString &value);
    ///设置测试结果
    /**
      @return value 测试结果
      @see result()
      */
    void setResult(const bool &value);
    ///设置错误信息
    /**
      @param value 错误信息
      @see errorMessage()
      */
    void setErrorMessage(const QString &value);
    ///设置错误所在行号
    /**
      @param value 错误所在行号
      @see errorLine()
      */
    void setErrorLine(const int &value);
    ///设置错误所在文件
    /**
      @param value 错误所在文件
      @see errorFile()
      */
    void setErrorFile(const QString &value);
    ///设置测试用例是否已经执行
    /**
      @param value 测试用例是否已经执行
      @see executed()
      */
    void setExecuted(const bool &value);
    ///设置测试用例是否需要执行
    /**
      @param value 测试用例是否需要执行
      @see checked()
      */
    void setChecked(const bool &value);

    ///判断测试用例是否是初始化测试用例或者清理测试用例
    /**
      如果当前用例是初始化用例或者清理测试用例,则返回true,否则返回false
      @see INIT_TEST_CASE
      @see CLEAN_TEST_CASE
      */
    bool isInitOrClean();
private:
    ///测试用例名
    QString _name;
    ///测试结果
    QString _resultStr;
    ///测试结果
    bool _result;
    ///错误信息
    QString _errorMessage;
    ///错误所在行号
    int _errorLine;
    ///错误所在文件
    QString _errorFile;
    ///测试用例是否已经执行
    bool _executed;
    ///测试用例是否需要执行
    bool _checked;
    ///调试信息
    QStringList _message;
    ///benchmark信息
    QStringList _benchmark;
};

#endif // TESTCASE_H
