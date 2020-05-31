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
    proc_ = new QProcess();
    stdout_ = tr("Starting the script...");
    connect(proc_, SIGNAL(readyReadStandardOutput()), this, SLOT(refreshConsole()));
    connect(proc_, SIGNAL(readyReadStandardError()), this, SLOT(refreshConsole()));
    proc_->start("/media/flash/test_script.sh");
    return true;
}

bool SshdServer::stop()
{
    proc_->kill();
    return true;
}

bool SshdServer::isRunning()
{
    return true;
}

void SshdServer::refreshConsole()
{
    stdout_ += proc_->readAllStandardOutput();
    stdout_ += proc_->readAllStandardError();
    emit valueChanged(stdout_);
}

QString SshdServer::getStandardOutput()
{
    return stdout_;
}
