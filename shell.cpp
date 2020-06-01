#include <QProcess>

#include "onyx/data/configuration.h"
#include "onyx/ui/languages.h"
#include "shell.h"

ShellServer::ShellServer()
{
}

ShellServer::~ShellServer()
{
}

bool ShellServer::start()
{
    proc_ = new QProcess();
    stdout_ = tr("Starting the script...");
    connect(proc_, SIGNAL(readyReadStandardOutput()), this, SLOT(refreshConsole()));
    connect(proc_, SIGNAL(readyReadStandardError()), this, SLOT(refreshConsole()));
    proc_->start("/usr/local/bin/m92shell_start.sh");
    return true;
}

bool ShellServer::stop()
{
    proc_->kill();
    return true;
}

bool ShellServer::isRunning()
{
    return true;
}

void ShellServer::refreshConsole()
{
    QString stdout = proc_->readAllStandardOutput();
    QString stderr = proc_->readAllStandardError();
    stdout_ += stdout;
    stdout_ += stderr;
    emit valueChanged(stdout + stderr);
}

QString ShellServer::getStandardOutput()
{
    return stdout_;
}
