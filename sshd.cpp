#include <QProcess>

#include "onyx/data/configuration.h"
#include "onyx/ui/languages.h"
#include "sshd.h"

SshdServer::SshdServer()
{
}

SshdServer::~SshdServer()
{
}

bool SshdServer::start()
{
    QProcess::startDetached("/usr/local/etc/sshd start");
    return true;
}

bool SshdServer::stop()
{
    QProcess::startDetached("/usr/local/etc/sshd stop");
    return true;
}

bool SshdServer::isRunning()
{
    return true;
}

