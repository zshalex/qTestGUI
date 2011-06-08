#ifndef TESTMANAGER_H
#define TESTMANAGER_H

#include <QList>
#include <QStringList>
#include <QDomDocument>
#include "testcase.h"

class TestManager
{
public:
    typedef QList<TestCase *> TestCaseList;

    TestManager();

    void initFromFunctions(const QStringList &funList);
    const int &indexOfByFunName(const QString &fun) const;
    void setTestResult(const QString &result);

    int count() const;
    void clear();
    void addTestCase(TestCase *testCase);
    TestCase *testCase(int index);
private:
    void readFunction(const QDomElement &element);
    void readResult(const QDomElement &element, TestCase *test);
    void readErrorMessage(const QDomElement &element, TestCase *test);

    TestCaseList _testList;
};

#endif // TESTMANAGER_H
