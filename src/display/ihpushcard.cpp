#include "ihpushcard.h"
#include "imageloader.h"
#include <QEvent>
#include <QHBoxLayout>
#include <QPainter>
#include <QPainterPath>

IHPushCard::IHPushCard(QWidget *parent) : QFrame(parent) {
    setupUI();

    installEventFilter(this);
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
    return QFrame::eventFilter(watched, event);
}

void IHPushCard::setupUI() {
    setMinimumWidth(100);
    setMinimumHeight(90);
    setStyleSheet("border: 1px hidden gray; border-radius: 10px;");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    itemNumberLabel = new QLabel(this);
    itemNumberLabel->setFixedWidth(20);
    itemNumberLabel->setStyleSheet(
        "border:none; font-size: 20px; font-weight: bold;");

    itemIconLabel = new QLabel(this);
    itemIconLabel->setFixedSize(QSize(52, 52));
    itemIconLabel->setStyleSheet("border: 1px solid gray; border-radius: 26px;");

    QObject::connect(new ImageLoader, &ImageLoader::imageLoaded, this,
                     [this](QPixmap *pixmap) {
                         if (pixmap) {
            itemIconLabel->setPixmap(
                                 ImageLoader::circularPixmap(*pixmap));
                             itemIconLabel->setScaledContents(true);
                         }
                         delete pixmap;
    });

    itemTextLabel = new QLabel(this);
    itemTextLabel->setText(
        QString("<b>Heading</b><p>%1</p>").arg("This is a text"));
    itemTextLabel->setStyleSheet("border:none;");

    auto itemLayout = new QHBoxLayout;
    itemLayout->addWidget(itemNumberLabel);
    itemLayout->addWidget(itemIconLabel);
    itemLayout->addWidget(itemTextLabel);
    itemLayout->setSpacing(5);
    itemLayout->setContentsMargins(10, 2, 1, 2);

    setLayout(itemLayout);
}
