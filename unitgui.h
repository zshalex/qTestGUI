#ifndef UNITGUI_H
#define UNITGUI_H

#include <QDialog>
#include <QProcess>

namespace Ui {
    class UnitGui;
}

class UnitGui : public QDialog
{
    Q_OBJECT

public:
    explicit UnitGui(QWidget *parent = 0);
    ~UnitGui();

    const QString &fileName() const {return _fileName;}

    void setFileName(const QString &value);
private slots:
    void runTest();
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
private:
    Ui::UnitGui *ui;

    QString _fileName;
    QStringList _arguments;
    QProcess *_process;

    void showResult(QByteArray array);
};

#endif // UNITGUI_H
