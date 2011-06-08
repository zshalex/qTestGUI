#ifndef TESTPROCESS_H
#define TESTPROCESS_H

#include <QProcess>
#include <QString>
#include <QStringList>
#include "testmanager.h"

class TestProcess
{
public:
    TestProcess();
    ~TestProcess();

    QStringList getFunList();
    QString getTestResult(TestManager &testManager);

    const QString &testFile() {return _testFile;}

    void setTestFile(const QString &value);
private:
    QProcess *_process;
    QString _testFile;
};

#endif // TESTPROCESS_H
