#ifndef SHELL_SHELL_H_
#define SHELL_SHELL_H_

#include <QMap>
#include <QString>

#include "onyx/base/base.h"
#include "onyx/ui/ui.h"
#include "onyx/base/dbus.h"

class ShellServer : public QObject
{
    Q_OBJECT;

public:
    ShellServer();
    ~ShellServer();
    QProcess *proc_;

public Q_SLOTS:
    bool start();
    bool stop();
    bool isRunning();
    QString getStandardOutput();
    void refreshConsole();

Q_SIGNALS:
    void valueChanged(QString newValue);

private:
    QMap<QString, QString> options_;
    QString stdout_;
};

#endif
