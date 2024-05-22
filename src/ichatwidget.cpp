#include "ichatwidget.h"
#include <QPainter>

IAutoResizeTextBrowser::IAutoResizeTextBrowser(QWidget *parent) : QTextBrowser(parent) {
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFrameShape(QFrame::NoFrame);

    connect(this, &QTextEdit::textChanged, this, &IAutoResizeTextBrowser::updateHeight);

    updateHeight();
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
    : QFrame(parent)
    , messageText(new IAutoResizeTextBrowser(this)){
    setFrameShape(QFrame::NoFrame);

    // 设置头像布局
    QVBoxLayout* avatarLayout = new QVBoxLayout();
    avatarLayout->setAlignment(Qt::AlignTop);
    QLabel* avatarLabel = new QLabel();
    avatarLabel->setPixmap(avatar.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    avatarLabel->setFixedWidth(30);
    avatarLayout->addWidget(avatarLabel);

    // 设置文本布局
    QVBoxLayout* textLayout = new QVBoxLayout();
    QLabel* userNameLabel = new QLabel(userName, this);
    userNameLabel->setFont(QFont("Yahei", 10, QFont::Bold));
    textLayout->addWidget(userNameLabel);
    textLayout->addWidget(messageText);

    // 设置主布局
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->addLayout(avatarLayout);
    mainLayout->addLayout(textLayout);
    setLayout(mainLayout);

    initAnimation();
    appendMessage(message);
    finish();
}

void IMessageWidget::initAnimation() {
    // 设置按钮
    button = new QPushButton(messageText->parentWidget());
    button->setFixedSize(20, 20);
    button->setStyleSheet("text-align:center;");

    auto createCircleIcon = [](const QSize &size, const QColor &color) {
        QPixmap pixmap(size);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(color);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(pixmap.rect());
        return QIcon(pixmap);
    };

    button->setIcon(createCircleIcon(QSize(16, 16), Qt::black));
    button->setIconSize(QSize(10, 10));

    // 创建动画
    animation = new QPropertyAnimation(button, "iconSize");
    animation->setDuration(900);
    animation->setStartValue(QSize(10, 10));
    animation->setKeyValueAt(0.5, QSize(16, 16));
    animation->setEndValue(QSize(10, 10));
    animation->setLoopCount(-1);
    animation->start();
    button->show();
}


void IMessageWidget::resizeEvent(QResizeEvent* event) {
    QFrame::resizeEvent(event);
    button->setGeometry(messageText->geometry());
}

void IMessageWidget::appendMessage(const QString &message) {
    if (message.isEmpty()) return;
    button->hide();
    animation->stop();
    text += message;
    messageText->setMarkdown(text + QString::fromUtf8("\u26AB"));
}


IChatWidget::IChatWidget(QWidget *parent)
    : QScrollArea(parent)
    , latestMessageWidget(nullptr) {
    setWidgetResizable(true);
    setFrameShape(QFrame::NoFrame);
    setStyleSheet("background-color: white;");

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
    latestMessageWidget = messageWidget;

    QTimer::singleShot(0, this, &IChatWidget::scrollToBottom);
}

bool IChatWidget::isNew() {
    return latestMessageWidget == nullptr;
}

IMessageWidget* IChatWidget::getLatestMessageWidget() const {
    return latestMessageWidget;
}

void IChatWidget::scrollToBottom() {
    verticalScrollBar()->setValue(verticalScrollBar()->maximum());
}
