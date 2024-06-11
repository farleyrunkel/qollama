#include "ichatscrollarea.h"
#include <QScrollBar>

IChatScrollArea::IChatScrollArea(QWidget *parent)
    : QScrollArea(parent), messageBoxes(), m_chatContainer(new QWidget(this)) {

    setupMainUI();
}

void IChatScrollArea::setupMainUI() {
    setWidgetResizable(true);
    setContentsMargins(0, 0, 0, 0);
    setWidget(m_chatContainer);

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
                                 const QString &avatar) {
    IMessageBox *messageWidget = new IMessageBox(userName, avatar, message, this);
    m_chatContainer->layout()->addWidget(messageWidget);
    messageBoxes.append(messageWidget);

    QTimer::singleShot(0, this, &IChatScrollArea::scrollToBottom);
}

bool IChatScrollArea::isEmpty() const { return messageBoxes.isEmpty(); }

IMessageBox *IChatScrollArea::getLatestMessageWidget() const {
    return messageBoxes.back();
}

void IChatScrollArea::scrollToBottom() {
    verticalScrollBar()->setValue(verticalScrollBar()->maximum());
}
