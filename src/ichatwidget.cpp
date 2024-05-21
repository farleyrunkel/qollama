#include "ichatwidget.h"


IAutoResizeTextBrowser::IAutoResizeTextBrowser(QWidget *parent) : QTextBrowser(parent) {
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);\
        setFrameShape(Shape::NoFrame);
    updateHeight();

    connect(this, &QTextEdit::textChanged, this, &IAutoResizeTextBrowser::updateHeight);
}

void IAutoResizeTextBrowser::resizeEvent(QResizeEvent *event) {
    QTextEdit::resizeEvent(event);
    updateHeight();
}

void IAutoResizeTextBrowser::updateHeight() {
    document()->setTextWidth(width()-5);
    setFixedHeight(document()->size().height());
}

IMessageWidget::IMessageWidget(const QString &userName, const QPixmap &avatar, const QString &message, QWidget *parent)
    : QWidget(parent), messageText(nullptr) {
    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    QVBoxLayout* avatarLayout = new QVBoxLayout();
    avatarLayout->setAlignment(Qt::AlignTop);
    QLabel* avatarLabel = new QLabel();
    avatarLabel->setPixmap(avatar.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    avatarLabel->setFixedWidth(35);
    avatarLayout->addWidget(avatarLabel);

    QVBoxLayout* textLayout = new QVBoxLayout();
    QLabel* userNameLabel = new QLabel(userName, this);
    userNameLabel->setFrameShape(QFrame::Shape::NoFrame);
    messageText = new IAutoResizeTextBrowser(this);
    messageText->setMarkdown(message);

    textLayout->addWidget(userNameLabel);
    textLayout->addWidget(messageText);

    mainLayout->addLayout(avatarLayout);
    mainLayout->addLayout(textLayout);
    setLayout(mainLayout);
}

void IMessageWidget::appendMessage(const QString &message) {
    text += message;
    messageText->setMarkdown(text);
}

IChatWidget::IChatWidget(QWidget *parent) : QScrollArea(parent) {
    setWidgetResizable(true);
    setFrameShape(Shape::NoFrame);
    setStyleSheet("background-color: white;");
    latestMessageWidget = nullptr;
    chatContainer = new QWidget(this);
    chatLayout = new QVBoxLayout(chatContainer);
    chatLayout->setAlignment(Qt::AlignTop);
    chatContainer->setLayout(chatLayout);

    setWidget(chatContainer);
}

void IChatWidget::addMessage(const QString &userName, const QPixmap &avatar, const QString &message) {
    IMessageWidget* messageWidget = new IMessageWidget(userName, avatar, message, this);
    chatLayout->addWidget(messageWidget);

    latestMessageWidget = messageWidget; // Store the latest message widget
    QTimer::singleShot(0, this, &IChatWidget::scrollToBottom);
}

bool IChatWidget::isNew() {
    return latestMessageWidget == nullptr;
}

IMessageWidget *IChatWidget::getLatestMessageWidget() const {
    return latestMessageWidget;
}

void IChatWidget::scrollToBottom() {
    verticalScrollBar()->setValue(verticalScrollBar()->maximum());
}
