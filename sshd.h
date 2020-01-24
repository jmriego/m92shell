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

public Q_SLOTS:
    bool start();
    bool stop();
    bool isRunning();

private:
    QMap<QString, QString> options_;
};

#endif
