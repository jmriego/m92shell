#ifndef SSHD_SSHD_H_
#define SSHD_SSHD_H_

#include <QMap>
#include <QString>

#include "onyx/base/base.h"
#include "onyx/ui/ui.h"
#include "onyx/base/dbus.h"

class SshdServer : public QObject
{
    Q_OBJECT;

public:
    SshdServer();
    ~SshdServer();
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
