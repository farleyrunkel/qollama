#include "ichatwidget.h"
#include <QPainter>

IAutoResizeTextBrowser::IAutoResizeTextBrowser(QWidget *parent) : QTextBrowser(parent) {
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFrameShape(QFrame::Shape::NoFrame);
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


QIcon createCircleIcon(const QSize &size, const QColor &color) {
    QPixmap pixmap(size);
    pixmap.fill(Qt::transparent); // 透明背景

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(color);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(QRect(0, 0, size.width(), size.height()));

    return QIcon(pixmap);
}

IMessageWidget::IMessageWidget(const QString &userName, const QPixmap &avatar, const QString &message, QWidget *parent)
    : QFrame(parent), messageText(nullptr) {
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    setFrameShape(QFrame::Shape::NoFrame);
    QVBoxLayout* avatarLayout = new QVBoxLayout();
    avatarLayout->setAlignment(Qt::AlignTop);
    QLabel* avatarLabel = new QLabel();
    avatarLabel->setPixmap(avatar.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    avatarLabel->setFixedWidth(30);

    avatarLayout->addWidget(avatarLabel);

    QVBoxLayout* textLayout = new QVBoxLayout();
    QLabel* userNameLabel = new QLabel(userName, this);
    userNameLabel->setFrameShape(QFrame::Shape::NoFrame);
    userNameLabel->setFont(QFont("Yahei", 10, QFont::Bold));
    messageText = new IAutoResizeTextBrowser(this);

    textLayout->addWidget(userNameLabel);
    textLayout->addWidget(messageText);

    mainLayout->addLayout(avatarLayout);
    mainLayout->addLayout(textLayout);
    setLayout(mainLayout);


    button = new QPushButton(messageText->parentWidget());

    button->setFixedSize(QSize(20, 20));
    button->setStyleSheet("text-align:center;");

    // 创建黑色实心圆图标
    QIcon icon = createCircleIcon(QSize(16, 16), Qt::black);
    button->setIcon(icon);

    // 设置初始图标大小
    QSize initialSize(10, 10);
    button->setIconSize(initialSize);

    // 创建动画
    animation = new QPropertyAnimation(button, "iconSize");
    animation->setDuration(900);
    animation->setStartValue(initialSize);
    animation->setKeyValueAt(0.5, QSize(16, 16)); // 放大到128x128
    animation->setEndValue(initialSize);
    animation->setLoopCount(-1); // 无限循环

    // 开始动画
    animation->start();
    button->show();

    appendMessage(message);
    finish();
}

void IMessageWidget::resizeEvent(QResizeEvent* event) {
    QFrame::resizeEvent(event);
    button->setGeometry(messageText->geometry());
}

void IMessageWidget::appendMessage(const QString &message) {
    if (message.isEmpty()) {
        return;
    }
    button->hide();
    animation->stop();
    text += message;
    messageText->setMarkdown(text +  QString::fromUtf8("\u26AB"));
}

IChatWidget::IChatWidget(QWidget *parent) : QScrollArea(parent) {
    setWidgetResizable(true);
    setFrameShape(QFrame::Shape::NoFrame);
    setStyleSheet("background-color: white;");
    latestMessageWidget = nullptr;
    chatContainer = new QWidget(this);
    chatLayout = new QVBoxLayout(chatContainer);
    chatLayout->setContentsMargins(40, 0, 40, 0);
    chatLayout->setSpacing(0);
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
