#include "ichatscrollarea.h"
#include <QScrollBar>

IChatScrollArea::IChatScrollArea(QWidget *parent)
    : QScrollArea(parent), m_latestMessageWidget(nullptr),
    m_chatContainer(new QWidget(this)) {
    setupUI();
}

void IChatScrollArea::setupUI() {
    setWidgetResizable(true);
    setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *chatLayout = new QVBoxLayout(m_chatContainer);
    chatLayout->setContentsMargins(40, 0, 40, 0);
    chatLayout->setSpacing(0);
    chatLayout->setAlignment(Qt::AlignTop);
    m_chatContainer->setLayout(chatLayout);
    m_chatContainer->setObjectName("chatContainer");
    m_chatContainer->setStyleSheet("background-color:white;");
    setWidget(m_chatContainer);
}

void IChatScrollArea::addMessage(const QString &message,
                                 const QString &userName,
                                 const QPixmap &avatar) {
    IMessageBox *messageWidget =
        new IMessageBox(userName, avatar.scaledToWidth(30), message, this);
    m_chatContainer->layout()->addWidget(messageWidget);
    m_latestMessageWidget = messageWidget;

    QTimer::singleShot(0, this, &IChatScrollArea::scrollToBottom);
}

bool IChatScrollArea::isNew() const { return m_latestMessageWidget == nullptr; }

IMessageBox *IChatScrollArea::getLatestMessageWidget() const {
    return m_latestMessageWidget;
}

void IChatScrollArea::scrollToBottom() {
    verticalScrollBar()->setValue(verticalScrollBar()->maximum());
}
