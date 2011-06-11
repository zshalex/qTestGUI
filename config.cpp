#include "config.h"

#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QTextStream>

const char* Config::optString = "t:rRlL";

const struct option Config::longOpts[] = {
        { "test", required_argument, NULL, 't' },
        { "autoRun", no_argument, NULL, 'r' },
        { "notAutoRun", no_argument, NULL, 'R' },
        { "autoLoad", no_argument, NULL, 'l' },
        { "notAutoLoad", no_argument, NULL, 'L'},
        { NULL, no_argument, NULL, 0 }
    };

Config::Config():_autoRun(true),_autoLoad(true)
{
}

void Config::setAutoRun(const bool &value)
{
    _autoRun = value;
}

void Config::setAutoLoad(const bool &value)
{
    _autoLoad = value;
}

void Config::setTestFile(const QString &value)
{
    _testFile = value;
}

void Config::setAppPath(QString value)
{
    _appPath = value;
}

void Config::loadFromFile(const QString fileName)
{
    QDomDocument doc("qTestGUI");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return;
    if (!doc.setContent(&file)) {
        file.close();
        return;
    }
    file.close();

    QDomElement root  = doc.documentElement();
    QDomElement node = root.firstChildElement();
    while (!node.isNull()) {
        if (node.tagName() == "autoRun")
            _autoRun = node.attribute("value") == "true" ? true : false;
        else if (node.tagName() == "autoLoad")
            _autoLoad = node.attribute("value") == "true" ? true : false;
        node = node.nextSiblingElement();
    }
}

void Config::loadFromArg(int argc, char *argv[])
{
    int longIndex;
    int opt = getopt_long( argc, argv, optString, longOpts, &longIndex );
    while( opt != -1 ) {
        switch( opt ) {
            case 't':
                _testFile = optarg;
                break;
            case 'r':
                _autoRun = true;
                break;
            case 'R':
                _autoRun = false;
                break;
            case 'l':
                _autoLoad = true;
                break;
            case 'L':
                _autoLoad = false;
                break;
            default:
                break;
        }

        opt = getopt_long( argc, argv, optString, longOpts, &longIndex);
    }
}

void Config::saveToFile(const QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
      return;
    QTextStream out(&file);

    QDomDocument doc("qTestGUI");

    QDomElement root = doc.createElement("qTestGUI");
    doc.appendChild(root);

    QDomElement autoRun = doc.createElement("autoRun");
    if (_autoRun)
        autoRun.setAttribute("value","true");
    else
        autoRun.setAttribute("value","false");
    root.appendChild(autoRun);


    QDomElement autoLoad = doc.createElement("autoLoad");
    if (_autoLoad)
        autoLoad.setAttribute("value","true");
    else
        autoLoad.setAttribute("value","false");
    root.appendChild(autoLoad);

    doc.save(out,4);
}
