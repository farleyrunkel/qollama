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
    spinFrame = new QFrame(messageText->parentWidget());
    spinFrame->setFixedSize(QSize(20, 20));
    auto layout = new QVBoxLayout(this);
    auto spinner = new WaitingSpinnerWidget(messageText->parentWidget());
    spinner->setFixedSize(QSize(10, 10));
    spinner->setRoundness(100.0);
    spinner->setMinimumTrailOpacity(15.0);
    spinner->setTrailFadePercentage(10.0);
    spinner->setNumberOfLines(10);
    spinner->setLineLength(10);
    spinner->setLineWidth(10);
    spinner->setInnerRadius(0);
    spinner->setRevolutionsPerSecond(1);
    spinner->setColor(QColor(84, 210, 99));
    spinner->setStyleSheet("border: 1px solid red;");

    layout->addWidget(spinner);
    spinFrame->setLayout(layout);

    spinner->start(); // gets the show on the road!

}


void IMessageWidget::resizeEvent(QResizeEvent* event) {
    QFrame::resizeEvent(event);

    spinFrame->setGeometry(messageText->geometry());
}

void IMessageWidget::finish() {
    messageText->setMarkdown(text);
}

void IMessageWidget::appendMessage(const QString &message) {
    if (message.isEmpty()) return;
    spinFrame->close();
    text += message;

    messageText->setMarkdown(text);
    QString html = messageText->toHtml();

    QString circleSpan = "<img src=':/icon/qtcircle.svg' height='11' width='11'/>";

    if (html.contains("</p></body></html>")) {
        html = html.replace("</p></body></html>", circleSpan + "</p></body></html>");
    }
    else if (html.contains("</li></ol></body></html>")) {
        html = html.replace("</li></ol></body></html>", circleSpan + "</li></ol></body></html>");
    }
    else if (html.contains("</li></ul></body></html>")) {
        html = html.replace("</li></ul></body></html>", circleSpan + "</li></ul></body></html>");
    }

    messageText->setHtml(html);

    qDebug() << "messageText->toHtml()" << messageText->toHtml();
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
