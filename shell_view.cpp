#include <QtGui/QtGui>
#include "shell_view.h"
#include "onyx/screen/screen_update_watcher.h"

#include "onyx/wireless/wifi_dialog.h"
#include "onyx/sys/sys_status.h"
#include "onyx/sys/platform.h"
#include "onyx/data/configuration.h"

static const int BUTTON_HEIGHT = 100;

DSView::DSView(QWidget *parent)
#ifndef Q_WS_QWS
    : QWidget(0, 0)
#else
    : QWidget(0, Qt::FramelessWindowHint)
#endif
    , page_(this)
    , text_(tr(""), 0)
    , start_(tr("Start"), 0)
    , close_(tr("Close"), 0)
{
    createLayout();
    onyx::screen::watcher().addWatcher(this);
    onyx::screen::watcher().enqueue(this, onyx::screen::ScreenProxy::GC);
}

DSView::~DSView()
{
}

void DSView::configNetwork()
{
    QString type = sys::SysStatus::instance().connectionType();
    if (type.contains("wifi", Qt::CaseInsensitive))
    {
        wifiDialog().popup(true);
    }
}

WifiDialog & DSView::wifiDialog()
{
    if (!conf_dialog_)
    {
        conf_dialog_.reset(new WifiDialog(0, SysStatus::instance()));
    }
    return *conf_dialog_;
}

void DSView::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
    case Qt::Key_Down:
    case Qt::Key_Up:
        break;
    default:
        QWidget::keyPressEvent(e);
        break;
    }
    e->accept();
}

void DSView::keyReleaseEvent(QKeyEvent *ke)
{
    switch (ke->key())
    {
    case ui::Device_Menu_Key:
        break;
    case Qt::Key_Left:
        break;
    case Qt::Key_Right:
        break;
    case Qt::Key_PageDown:
        break;
    case Qt::Key_Down:
        break;
    case Qt::Key_PageUp:
        break;
    case Qt::Key_Up:
        break;
    case Qt::Key_C:
        break;
    case Qt::Key_Escape:
    case Qt::Key_Home:
        onCloseClicked();
    default:
        QWidget::keyReleaseEvent(ke);
        break;
    }
    ke->ignore();
}

void DSView::closeEvent(QCloseEvent * event)
{
    QWidget::closeEvent(event);
}

/// Ignore the double click event.
void DSView::mouseDoubleClickEvent(QMouseEvent*me)
{
    me->accept();
}

bool DSView::eventFilter(QObject *obj, QEvent *e)
{
    qDebug("Select event:%d", e->type());
    if (e->type() == QEvent::MouseButtonRelease && obj->isWidgetType())
    {
        onyx::screen::instance().updateWidget(0, onyx::screen::ScreenProxy::GU);
    }
    return QObject::eventFilter(obj, e);
}

void DSView::onStartClicked()
{
    configNetwork();
    connect(&shell_, SIGNAL(valueChanged(QString)), this, SLOT(onStandardOutput(QString)));
    shell_.start();
    update();
    onyx::screen::watcher().enqueue(this, onyx::screen::ScreenProxy::GC);
}

void DSView::onCloseClicked()
{
    shell_.stop();
    sys::SysStatus::instance().stopWpaSupplicant();
    qApp->exit();
}

void DSView::createLayout()
{
    start_.setFixedHeight(BUTTON_HEIGHT);
    close_.setFixedHeight(BUTTON_HEIGHT);
    text_.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    text_.setFontPointSize(16);
    page_.addWidget(&text_, 0, 0, 1, 2);
    page_.setRowMinimumHeight(0, 1130);
    page_.addWidget(&start_, 1, 0);
    page_.addWidget(&close_, 1, 1);
    this->setLayout(&page_);

    text_.show();
    start_.show();
    close_.show();
    this->show();

    connect(&start_, SIGNAL(clicked(bool)), this, SLOT(onStartClicked()));
    connect(&close_, SIGNAL(clicked(bool)), this, SLOT(onCloseClicked()));
    onyx::screen::watcher().enqueue(this, onyx::screen::ScreenProxy::GC);
}

bool DSView::start()
{
    onStartClicked();
    return true;
}

bool DSView::stop()
{
    onCloseClicked();
    return true;
}

bool DSView::exec(const QStringList & args)
{
    return true;
}

void DSView::onStandardOutput(QString newValue)
{
    qDebug() << newValue;
    text_.insertPlainText(newValue);
    update();
    qApp->processEvents();
    onyx::screen::instance().updateWidget(&text_, onyx::screen::ScreenProxy::GU);
}
