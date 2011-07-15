///配置信息
/**
  读取命令行参数,以及配置文件
  @author Alex Zhao
  @version 1.0
  */

#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <getopt.h>

class Config
{
public:
    ///getopt的短参数
    /**
      <p>-t:单元测试文件</p>
      <p>-r:自动运行测试</p>
      <p>-R:不自动运行测试</p>
      <p>-l:自动导入测试用例</p>
      <p>-L:不自动导入测试用例</p>
      */
    static const char *optString;
    ///getopt的长参数
    /**
      <p>--test:        单元测试文件</p>
      <p>--autoRun:     自动运行测试</p>
      <p>--notAutoRun:  不自动运行测试</p>
      <p>--autoLoad:    自动导入测试用例</p>
      <p>--notAutoLoad: 不自动导入测试用例</p>
      */
    static const struct option longOpts[];

    ///构造函数
    Config();

    ///读取配置文件
    /**
      @param fileName 配置文件名
      */
    void loadFromFile(const QString fileName);
    ///读取命令行参数
    /**
      @param argc 参数个数
      @param argv 参数值数组
      */
    void loadFromArg(int argc, char *argv[]);
    ///保存配置
    /**
      @param fileName 配置文件名
      */
    void saveToFile(const QString fileName);

    ///读取自动运行参数
    /**
      @return 自动运行参数
      */
    const bool &autoRun() const {return _autoRun;}
    ///读取自动导入参数
    /**
      @return 自动导入参数
      */
    const bool &autoLoad() const {return _autoLoad;}
    ///读取单元测试文件名
    /**
      @return 单元测试文件名
      */
    const QString &testFile() const {return _testFile;}
    ///读取应用程序路径
    /**
      @return 应用程序路径
      */
    const QString &appPath() const {return _appPath;}

    ///设置自动运行参数
    /**
      @param value 自动运行参数
      */
    void setAutoRun(const bool &value);
    ///设置自动导入参数
    /**
      @param value 自动导入参数
      */
    void setAutoLoad(const bool &value);
    ///设置单元测试文件名
    /**
      @param value 单元测试文件名
      */
    void setTestFile(const QString &value);
    ///设置应用程序路径
    /**
      @param value 应用程序路径
      */
    void setAppPath(QString value);
private:
    ///自动运行参数
    bool _autoRun;
    ///自动导入参数
    bool _autoLoad;
    ///单元测试文件名
    QString _testFile;
    ///应用程序路径
    QString _appPath;
};

#endif // CONFIG_H
