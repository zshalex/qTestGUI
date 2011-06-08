#include "testmanager.h"
#include <QDebug>

TestManager::TestManager():QList<TestCase>()
{

}

void TestManager::initFromFunctions(const QStringList &funList)
{
    int len = funList.length();
    clear();
    QString funName;
    for (int i = 0; i < len; i++) {
        TestCase test;
        funName = funList.at(i);
        funName.resize(funName.length() - 2);
        test.setName(funName);
        append(test);
    }
}

const int &TestManager::indexOfByFunName(const QString &fun) const
{
    int len = length();
    for (int i = 0; i < len; i++) {
        if (at(i).name() == fun) {
            return i;
        }
    }
    return -1;
}

void TestManager::setTestResult(const QString &result)
{
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
    QString funName = element.attribute("name");
    int index = indexOfByFunName(funName);
    qDebug() << "find" << index;
    if (index != -1) {
        TestCase *test = const_cast<TestCase *>(&at(index));
        QDomNode res = element.firstChild();
        if (!res.isNull() && test->checked()) {
            readResult(res.toElement(),test);
        } else {
//            test.setExecuted(false);
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
