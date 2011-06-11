#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <getopt.h>

class Config
{
public:
    static const char *optString;
    static const struct option longOpts[];

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
