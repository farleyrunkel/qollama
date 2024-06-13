#include "ihpushcard.h"
#include "imageloader.h"
#include "signalhub.h"
#include <QEvent>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QPainterPath>

IHPushCard::IHPushCard(QWidget *parent) : QPushButton(parent) {
    setupMainUI();

    installEventFilter(this);

    // Connect the clicked signal to the SignalHub's on_message_sent signal
    connect(this, &IHPushCard::clicked, [&]() {
        emit SignalHub::instance().on_message_sent(
            this->property("prompt").toString(), true);
    });
}

void IHPushCard::setupMainUI() {
    setMinimumWidth(120);
    setFixedHeight(60);
    setObjectName("bigButton");
    // setStyleSheet("border: 1px hidden gray; border-radius: 10px;");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(2, 2, 1, 2);

    setupNumberUI(mainLayout);
    setupIconUI(mainLayout);
    setupTextUI(mainLayout);
}

void IHPushCard::setupNumberUI(QHBoxLayout *layout) {
    itemNumberLabel = new QLabel(this);
    itemNumberLabel->setFixedWidth(40);
    itemNumberLabel->setStyleSheet(
        "border:none; font-size: 20px; font-weight: bold; text-align: center;");
    layout->addWidget(itemNumberLabel);
}

void IHPushCard::setupIconUI(QHBoxLayout *layout) {
    itemIconLabel = new QLabel(this);
    itemIconLabel->setFixedSize(QSize(42, 42));
    itemIconLabel->setStyleSheet(
        QString("border: 1px solid gray; border-radius: %1px;")
            .arg(itemIconLabel->height() / 2));
    layout->addWidget(itemIconLabel);

    QObject::connect(new ImageLoader, &ImageLoader::imageLoaded, this,
                     [this](QPixmap *pixmap) {
                         if (pixmap) {
            itemIconLabel->setPixmap(
                                 ImageLoader::circularPixmap(*pixmap));
                             itemIconLabel->setScaledContents(true);
                         }
                         delete pixmap;
    });
}

void IHPushCard::setupTextUI(QHBoxLayout *layout) {
    m_name = "Model";
    m_intro = "Introducing to model";
    itemTextLabel = new QLabel(this);
    itemTextLabel->setText(
        QString("<b>%1</b><p>%2</p>").arg(m_name).arg(m_intro));
    itemTextLabel->setStyleSheet("border:none;");
    itemTextLabel->setWordWrap(true);
    layout->addWidget(itemTextLabel);
}

void IHPushCard::setNumber(int num) { itemNumberLabel->setNum(num); }

void IHPushCard::setText(const QString &text) { itemTextLabel->setText(text); }

void IHPushCard::setNumberUnused() { itemNumberLabel->close(); }

void IHPushCard::setIcon(const QIcon &icon) {
    itemIconLabel->setPixmap(icon.pixmap(itemIconLabel->width()));
}

bool IHPushCard::eventFilter(QObject *watched, QEvent *event) {
    if (watched == this) {
        if (event->type() == QEvent::Enter) {
            qDebug() << "Mouse entered";
            setStyleSheet("border: 1px solid #ececec; border-radius: 10px; "
                          "background-color: #ececec;");
        } else if (event->type() == QEvent::Leave) {
            qDebug() << "Mouse left";
            setStyleSheet("border: 1px hidden #ececec; border-radius: 10px; "
                          "background-color: none;");
        }
    }
    return QPushButton::eventFilter(watched, event);
}

void IHPushCard::setName(const QString &name) {
    m_name = name;
    itemTextLabel->setText(
        QString("<b>%1</b><p>%2</p>").arg(m_name).arg(m_intro));
}

void IHPushCard::setIntro(const QString &intro) {
    m_intro = intro;
    itemTextLabel->setText(
        QString("<b>%1</b><p>%2</p>").arg(m_name).arg(m_intro));
}
