#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <getopt.h>

static const char *optString = "t:rRlL";

static const struct option longOpts[] = {
    { "test", required_argument, NULL, 't' },
    { "autoRun", no_argument, NULL, 'r' },
    { "notAutoRun", no_argument, NULL, 'R' },
    { "autoLoad", no_argument, NULL, 'l' },
    { "notAutoLoad", no_argument, NULL, 'L'},
    { NULL, no_argument, NULL, 0 }
};

class Config
{
public:
    Config();

    void loadFromFile(const QString fileName);
    void loadFromArg(int argc, char *argv[]);
    void saveToFile(const QString fileName);

    const bool &autoRun() const {return _autoRun;}
    const bool &autoLoad() const {return _autoLoad;}
    const QString &testFile() const {return _testFile;}
    const QString &appPath() const {return _appPath;}

    void setAutoRun(const bool &value);
    void setAutoLoad(const bool &value);
    void setTestFile(const QString &value);
    void setAppPath(QString value);
private:
    bool _autoRun;
    bool _autoLoad;
    QString _testFile;
    QString _appPath;
};

#endif // CONFIG_H
