#include "ivpushcard.h"
#include "signalhub.h"

IVPushCard::IVPushCard(QWidget *parent) : QPushButton(parent) {
    setupUI();

    // Connect the clicked signal to the SignalHub's on_message_sent signal
    connect(this, &IVPushCard::clicked, [&]() {
        emit SignalHub::instance().on_message_sent(m_textLabel->text(), true);
    });
}

IVPushCard::IVPushCard(const QString &text, QWidget *parent)
    : IVPushCard(parent) {
    setText(text);
}

IVPushCard::IVPushCard(const QIcon &icon, const QString &text, QWidget *parent)
    : IVPushCard(parent) {
    setText(text);
    setPixmap(icon.pixmap(m_iconLabel->size()));
}

void IVPushCard::setupUI() {
    setObjectName("ivPushCard");
    setMinimumSize(QSize(120, 120));
    setMaximumSize(QSize(200, 150));

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setSizePolicy(sizePolicy);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    // Setup icon label
    m_iconLabel = new QLabel(this);
    m_iconLabel->setStyleSheet("border: none;");
    m_iconLabel->setMaximumSize(QSize(30, 30));
    m_iconLabel->setAlignment(Qt::AlignCenter); // Center align the icon label
    QPixmap pixmap(":/icon/electric-light-bulb.svg");
    m_iconLabel->setPixmap(pixmap.scaled(m_iconLabel->size()));
    mainLayout->addWidget(
        m_iconLabel, 0,
        Qt::AlignCenter); // Add icon label to layout and center align

    // Setup text label
    m_textLabel = new QLabel(this);
    m_textLabel->setSizePolicy(sizePolicy);
    m_textLabel->setAlignment(Qt::AlignCenter); // Center align the text label
    m_textLabel->setWordWrap(true);
    m_textLabel->setIndent(10);
    mainLayout->addWidget(
        m_textLabel, 0,
        Qt::AlignCenter); // Add text label to layout and center align
}

void IVPushCard::setText(const QString &text) { m_textLabel->setText(text); }

void IVPushCard::setPixmap(const QPixmap &pixmap) {
    m_iconLabel->setPixmap(pixmap.scaled(m_iconLabel->size()));
}
