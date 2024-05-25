#include "ipushcard.h"


IPushCard::IPushCard(QWidget *parent) : QFrame(parent)
{
    setupUI();
    // 安装事件过滤器
    installEventFilter(this);
}

void IPushCard::setText(const QString &text) {
    itemTextLabel->setText(text);
}

void IPushCard::setNumberUnused() {
    itemNumberLabel->close();
}

void IPushCard::setIcon(const QIcon &icon){
    itemIconLabel->setPixmap(icon.pixmap(itemIconLabel->width()));
}

bool IPushCard::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == this)
    {
        if (event->type() == QEvent::Enter)
        {
            qDebug() << "Mouse entered";
            setStyleSheet("border: 1px solid gray; border-radius: 10px; background-color: lightgray;");
        }
        else if (event->type() == QEvent::Leave)
        {
            qDebug() << "Mouse left";
            setStyleSheet("border: 1px hidden gray; border-radius: 10px; background-color: none;");
        }
    }
    return QFrame::eventFilter(watched, event);
}

void IPushCard::setupUI()
{
    setMinimumWidth(250);
    setMinimumHeight(90);
    setStyleSheet("border: 1px hidden gray; border-radius: 10px;");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    itemNumberLabel = new QLabel(this);
    itemNumberLabel->setNum(1);
    itemNumberLabel->setFixedWidth(20);
    itemNumberLabel->setStyleSheet("border:none; font-size: 20px; font-weight: bold;");

    itemIconLabel = new QLabel(this);
    itemIconLabel->setFixedSize(QSize(52, 52));
    itemIconLabel->setPixmap(QIcon("://icon/art-palette.svg").pixmap(itemIconLabel->width()));
    itemIconLabel->setStyleSheet("border: 1px solid gray; border-radius: 26px;");

    itemTextLabel = new QLabel(this);
    itemTextLabel->setText(QString("<b>Heading</b><p>%1</p>").arg("This is a text"));
    itemTextLabel->setStyleSheet("border:none;");

    auto itemLayout = new QHBoxLayout;
    itemLayout->addWidget(itemNumberLabel);
    itemLayout->addWidget(itemIconLabel);
    itemLayout->addWidget(itemTextLabel);
    itemLayout->setSpacing(5);
    itemLayout->setContentsMargins(10, 2, 1, 2);

    setLayout(itemLayout);
}
