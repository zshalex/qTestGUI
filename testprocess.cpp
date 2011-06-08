#include "testprocess.h"

TestProcess::TestProcess():_testFile("")
{
    _process = new QProcess();
}

TestProcess::~TestProcess()
{
    delete _process;
}

void TestProcess::setTestFile(const QString &value)
{
    _testFile = value;
}

QStringList TestProcess::getFunList()
{
    QStringList arg,result;
    arg << "-functions";
    _process->start(_testFile,arg);
    if (_process->waitForFinished()){
        while(!_process->atEnd())
            result << QString(_process->readLine()).trimmed();
    }
    return result;
}

QString TestProcess::getTestResult(TestManager &testManager)
{
    QStringList arg;
    QString result;
    for (int i = 0; i < testManager.count(); i++) {
        if (testManager.testCase(i)->checked())
            arg << testManager.testCase(i)->name();
    }
    arg << "-xml";
    _process->start(_testFile,arg);
    if (_process->waitForFinished()){
        result = _process->readAll();
    }
    return result;
}
