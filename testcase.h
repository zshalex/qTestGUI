#ifndef TESTCASE_H
#define TESTCASE_H

#include <QString>
#include <QStringList>

class TestCase
{
public:
    TestCase();

    const QString &name() const {return _name;}
    const QString &resultStr() const {return _resultStr;}
    const bool &result() const {return _result;}
    const QString &errorMessage() const {return _errorMessage;}
    const int &errorLine() const {return _errorLine;}
    const QString &errorFile() const {return _errorFile;}
    const bool &executed() const {return _executed;}
    const bool &checked() const {return _checked;}
    QStringList &message() {return _message;}
    QStringList &benchmark() {return _benchmark;}

    void setName(const QString &value);
    void setResultStr(const QString &value);
    void setResult(const bool &value);
    void setErrorMessage(const QString &value);
    void setErrorLine(const int &value);
    void setErrorFile(const QString &value);
    void setExecuted(const bool &value);
    void setChecked(const bool &value);
private:
    QString _name;
    QString _resultStr;
    bool _result;
    QString _errorMessage;
    int _errorLine;
    QString _errorFile;
    bool _executed;
    bool _checked;
    QStringList _message;
    QStringList _benchmark;
};

#endif // TESTCASE_H
