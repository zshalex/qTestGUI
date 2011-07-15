///测试用例的管理类
/**
  类中维护一个测试用例的列表,它根据测试用例列表初始化,
  并分析单元测试返回的xml,设置测试用例的测试信息.
  @author Alex Zhao
  @version 1.0
  */

#ifndef TESTMANAGER_H
#define TESTMANAGER_H

#include <QList>
#include <QStringList>
#include <QDomDocument>
#include "testcase.h"

class TestManager
{
public:
    ///测试用例列表
    typedef QList<TestCase *> TestCaseList;

    ///构造函数
    /**
      */
    TestManager();

    ///从测试用例列表初始化
    /**
      @param funList 测试用例列表
      */
    void initFromFunctions(const QStringList &funList);
    ///根据测试用例名找到测试用例的索引
    /**
      @param fun 测试用例名
      @return 测试用例的索引值
      */
    const int &indexOfByFunName(const QString &fun) const;
    ///设置测试结果
    /**
      @param result 测试结果,从TestProcess类返回
      */
    void setTestResult(const QString &result);

    ///测试用例数
    /**
      @return 测试用例数
      */
    int count() const;
    ///清空测试用例
    /**
      */
    void clear();
    ///添加测试用例
    /**
      @param testCase 测试用例
      */
    void addTestCase(TestCase *testCase);
    ///获取指定的测试用例
    /**
      @param index 测试用例索引
      @return 测试用例
      */
    TestCase *testCase(int index);
    ///保存测试结果
    /**
      @param filename 文件名
      */
    void saveResult(QString filename);
private:
    ///读取测试用例
    /**
      @param element xml中根的element对象
      */
    void readFunction(const QDomElement &element);
    ///读取测试结果
    /**
      @param element xml中测试用例的element对象
      @param test 测试用例
      */
    void readResult(const QDomElement &element, TestCase *test);
    ///读取错误信息
    /**
      @param element xml中测试用例的element对象
      @param test 测试用例
      */
    void readErrorMessage(const QDomElement &element, TestCase *test);
    ///读取调试信息
    /**
      @param element xml中测试用例的element对象
      @param test 测试用例
      */
    void readMessage(const QDomElement &element, TestCase *test);
    ///读取Benchmark信息
    /**
      @param element xml中测试用例的element对象
      @param test 测试用例
      */
    void readBenchmark(const QDomElement &element, TestCase *test);
private:
    ///测试用例列表
    TestCaseList _testList;
    ///测试结果
    QString _xmlStr;
    ///读取xml的对象
    QDomDocument _doc;
};

#endif // TESTMANAGER_H
