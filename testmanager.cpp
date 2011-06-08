#include "testmanager.h"
#include <QDebug>

TestManager::TestManager()
{

}

int TestManager::count() const
{
    return _testList.length();
}

void TestManager::clear()
{
    TestManager::TestCaseList::const_iterator itr = _testList.begin();
    while(itr != _testList.end()) {
        TestCase *tp = *itr;
        delete tp;
    }
    _testList.clear();
}

void TestManager::addTestCase(TestCase *testCase)
{
    _testList.append(testCase);
}

TestCase *TestManager::testCase(int index)
{
    TestCase *tp = NULL;
    if (index >= 0 && index < _testList.length()){
        tp = _testList.at(index);
    }
    return tp;
}

void TestManager::initFromFunctions(const QStringList &funList)
{
    int len = funList.length();
    clear();
    QString funName;
    for (int i = 0; i < len; i++) {
        TestCase *test = new TestCase();
        funName = funList.at(i);
        funName.resize(funName.length() - 2);
        test->setName(funName);
        addTestCase(test);
    }
}

const int &TestManager::indexOfByFunName(const QString &fun) const
{
    int len = count();
    for (int i = 0; i < len; i++) {
        if (_testList.at(i)->name() == fun) {
            return i;
        }
    }
    return -1;
}

void TestManager::setTestResult(const QString &result)
{
    qDebug() << result;
    QDomDocument doc;
    doc.setContent(result);
    QDomElement root = doc.documentElement();
    QDomNodeList funlist = root.elementsByTagName("TestFunction");
    for (int i = 0; i < funlist.count(); i++) {
        readFunction(funlist.at(i).toElement());
    }
}

void TestManager::readFunction(const QDomElement &element)
{
    qDebug() << "readFunction";
    QString funName = element.attribute("name");
    int index = indexOfByFunName(funName);
    if (index != -1) {
        //find test case
        qDebug() << 'find' << index;
        TestCase *test = _testList.at(index);
        QDomNode res = element.firstChild();
        if (!res.isNull() && test->checked()) {
            readResult(res.toElement(),test);
        } else {
            test->setChecked(false);
        }
    }
}

void TestManager::readResult(const QDomElement &element, TestCase *test)
{
    QString result = element.attribute("type");
    test->setExecuted(true);
    qDebug() << result;
    test->setResultStr(result);
    if (result == "pass") {
        test->setResult(true);
        test->setErrorFile("");
        test->setErrorLine(0);
        test->setErrorMessage("");
    } else if (result == "fail") {
        test->setResult(false);
        test->setErrorFile(element.attribute("file"));
        test->setErrorLine(element.attribute("line").toInt());
        test->setErrorMessage("");
        readErrorMessage(element,test);
    }
}

void TestManager::readErrorMessage(const QDomElement &element, TestCase *test)
{
    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        if (child.nodeName() == "Description") {
            test->setErrorMessage(child.toElement().firstChild().toCDATASection().data());
            break;
        }
        child = child.nextSibling();
    }
}
