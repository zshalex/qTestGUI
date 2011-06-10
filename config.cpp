#include "config.h"

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

}
