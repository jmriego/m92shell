#include <QtGui/QtGui>
#include "sshd_view.h"
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

void DSView::paintEvent(QPaintEvent *)
{
    update();
    // QPainter painter(this);
    // painter.fillRect(rect(), Qt::white);
    // QFont font = QApplication::font();
    // font.setPointSize(18);
    // painter.setFont(font);
    // QFontMetrics fm(font);

    // painter.drawText(QRect(10, 10, width()-20, height() - BUTTON_HEIGHT), Qt::AlignLeft | Qt::AlignTop, stdout_);

}

void DSView::onStartClicked()
{
    configNetwork();
    connect(&sshd_, SIGNAL(valueChanged(QString)), this, SLOT(onStandardOutput(QString)));
    sshd_.start();
    update();
    onyx::screen::watcher().enqueue(this, onyx::screen::ScreenProxy::GC);
}

void DSView::onCloseClicked()
{
    sshd_.stop();
    sys::SysStatus::instance().stopWpaSupplicant();
    qApp->exit();
}

void DSView::createLayout()
{
    text_.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    text_.setFixedHeight(1130);
    text_.setFontPointSize(18);
    buttons_.addWidget(&start_, 0, Qt::AlignBottom);
    buttons_.addWidget(&close_, 0, Qt::AlignBottom);
    page_.addWidget(&text_, 0, Qt::AlignTop);
    page_.addLayout(&buttons_, 1);

    start_.setFixedHeight(BUTTON_HEIGHT);
    close_.setFixedHeight(BUTTON_HEIGHT);

    connect(&start_, SIGNAL(clicked(bool)), this, SLOT(onStartClicked()));
    connect(&close_, SIGNAL(clicked(bool)), this, SLOT(onCloseClicked()));
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
    stdout_ = newValue;
    qDebug() << stdout_;
    text_.setText(stdout_);
    onyx::screen::instance().updateWidget(0, onyx::screen::ScreenProxy::GC);
}
