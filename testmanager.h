#ifndef TESTMANAGER_H
#define TESTMANAGER_H

#include <QList>
#include <QStringList>
#include <QDomDocument>
#include "testcase.h"

class TestManager : public QList<TestCase>
{
public:
    TestManager();

    void initFromFunctions(const QStringList &funList);
    const int &indexOfByFunName(const QString &fun) const;
    void setTestResult(const QString &result);
private:
    void readFunction(const QDomElement &element);
    void readResult(const QDomElement &element, TestCase *test);
    void readErrorMessage(const QDomElement &element, TestCase *test);
};

#endif // TESTMANAGER_H
