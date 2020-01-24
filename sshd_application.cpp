#include "onyx/data/configuration.h"
#include "onyx/ui/languages.h"
#include "sshd_application.h"


DSApplication::DSApplication(int &argc, char **argv)
    : QApplication(argc, argv)
{
    ui::loadTranslator(QLocale::system().name());

    QCoreApplication::setOrganizationName(QLatin1String("Onyx"));
    QCoreApplication::setApplicationName(QLatin1String("SSH Server"));
}

DSApplication::~DSApplication(void)
{
}

bool DSApplication::start()
{
    main_window_.showMaximized();
    main_window_.start();
    return true;
}

bool DSApplication::stop()
{
    return true;
}

bool DSApplication::execShellCommand(const QStringList &args)
{
    return true;
}


