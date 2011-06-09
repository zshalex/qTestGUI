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
    typedef enum {
        GetFunList = 0,
        RunTest = 1
    } TaskName;

    explicit TestProcess(QObject *parent = 0);
    ~TestProcess();

    bool getFunList();
    bool runTest(TestManager &testManager);

    const QString &testFile() {return _testFile;}

    void setTestFile(const QString &value);
signals:
    void testFinished(const QString &result);
    void getFunListFinished(const QStringList &result);
public slots:
    void processFinished(int exitCode);
private:
    QStringList getArgs(TestManager &testManager);
private:
    QProcess *_process;
    QString _testFile;
    TaskName _curTask;
};

#endif // TESTPROCESS_H
