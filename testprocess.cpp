#include "testprocess.h"
#include <QDebug>

TestProcess::TestProcess(QObject *parent):QObject(parent),_testFile(""),
    _curTask(GetFunList)
{
    _process = new QProcess();
    this->connect(_process,SIGNAL(finished(int)),this,SLOT(processFinished(int)));
}

TestProcess::~TestProcess()
{
    delete _process;
}

void TestProcess::setTestFile(const QString &value)
{
    _testFile = value;
}

bool TestProcess::getFunList()
{
    if (_process->state() == QProcess::NotRunning) {
        QStringList arg;
        arg << "-functions";
        _curTask = GetFunList;
        _process->start(_testFile,arg);
        return true;
    } else {
        return false;
    }
}

QStringList TestProcess::getArgs(TestManager &testManager)
{
    QStringList arg;
    for (int i = 0; i < testManager.count(); i++) {
        if (testManager.testCase(i)->name() == "initTestCase") {
            testManager.testCase(i)->setChecked(true);
            continue;
        }
        if (testManager.testCase(i)->name() == "cleanupTestCase") {
            testManager.testCase(i)->setChecked(true);
            continue;
        }
        if (testManager.testCase(i)->checked())
            arg << testManager.testCase(i)->name();
        testManager.testCase(i)->message().clear();
        testManager.testCase(i)->benchmark().clear();
    }
    arg << "-xml";
    return arg;
}

bool TestProcess::runTest(TestManager &testManager)
{
    if (_process->state() == QProcess::NotRunning) {
        QStringList arg = getArgs(testManager);
        _curTask = RunTest;
        _process->start(_testFile,arg);
        return true;
    } else {
        return false;
    }
}

void TestProcess::processFinished (int exitCode)
{
    switch(_curTask) {
        case GetFunList: {
            QStringList result;
            while(!_process->atEnd())
                result << QString(_process->readLine()).trimmed();
            emit getFunListFinished(result);
            break;
        }
        case RunTest: {
            emit testFinished(_process->readAll());
        }
    }
}
