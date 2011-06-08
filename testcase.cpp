#include "testcase.h"

TestCase::TestCase():_name(""),_result(false),
    _errorMessage(""),_errorLine(0),_errorFile(""),_executed(false),_checked(true)
{
}

void TestCase::setName(const QString &value)
{
    _name = value;
}

void TestCase::setResultStr(const QString &value)
{
    _resultStr = value;
}

void TestCase::setResult(const bool &value)
{
    _result = value;
}

void TestCase::setErrorMessage(const QString &value)
{
    _errorMessage = value;
}

void TestCase::setErrorLine(const int &value)
{
    _errorLine = value;
}

void TestCase::setErrorFile(const QString &value)
{
    _errorFile = value;
}

void TestCase::setExecuted(const bool &value)
{
    _executed = value;
}

void TestCase::setChecked(const bool &value)
{
    _checked = value;
}
