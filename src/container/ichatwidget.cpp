#include "ichatwidget.h"
#include <QPainter>
#include "waitingspinnerwidget.h"

IAutoResizeTextBrowser::IAutoResizeTextBrowser(QWidget *parent) : QTextBrowser(parent)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFrameShape(QFrame::NoFrame);

    connect(this, &IAutoResizeTextBrowser::textChanged, this, &IAutoResizeTextBrowser::updateGeometry);
}

void IAutoResizeTextBrowser::resizeEvent(QResizeEvent *event)
{
    QTextBrowser::resizeEvent(event);
    updateGeometry();
}

void IAutoResizeTextBrowser::updateGeometry()
{
    // Set the text width of the document to match the width of the text browser
    document()->setTextWidth(width());

    // Get the document height and set it as the fixed height of the text browser
    qreal docHeight = document()->size().height();
    setFixedHeight(static_cast<int>(docHeight));

    // Call the base class updateGeometry() method
    QTextBrowser::updateGeometry();
}


IMessageWidget::IMessageWidget(const QString &userName, const QPixmap &avatar, const QString &message, QWidget *parent)
    : QWidget(parent)
    , avatarLabel(new QLabel(this))
    , userLabel(new QLabel(userName, this))
    , messageBrowser(new IAutoResizeTextBrowser(this))
    , spinner(nullptr)
    , messageCache()
{
    setupUI();
    setPixmap(avatar);
    setAnimation();

    appendMessage(message);
    finish();
}

void IMessageWidget::setPixmap( const QPixmap &avatar)
{
    avatarLabel->setPixmap(avatar);
}

void IMessageWidget::setupUI()
{
    // 设置主布局
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    setLayout(mainLayout);

    // 设置头像布局
    QVBoxLayout* avatarLayout = new QVBoxLayout(this);
    avatarLayout->setAlignment(Qt::AlignTop);
    avatarLayout->addWidget(avatarLabel);

    // 设置文本布局
    QVBoxLayout* textLayout = new QVBoxLayout(this);
    userLabel->setFont(QFont("Yahei", 10, QFont::Bold));
    textLayout->addWidget(userLabel);
    textLayout->addWidget(messageBrowser);

    mainLayout->addLayout(avatarLayout, 0);
    mainLayout->addLayout(textLayout, 1);
}

void IMessageWidget::setAnimation()
{
    auto spinFrame = new QFrame(this);
    spinFrame->setFixedSize(QSize(20, 20));
    auto layout = new QVBoxLayout(spinFrame);
    spinner = new WaitingSpinnerWidget(spinFrame);

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

    layout->addWidget(spinner);
    spinFrame->setLayout(layout);

    spinner->start(); // gets the show on the road!
}

void IMessageWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    spinner->parentWidget()->setGeometry(messageBrowser->geometry());
}

void IMessageWidget::setMarkdown(const QString &markdown)
{
    messageBrowser->setMarkdown(markdown);
}

void IMessageWidget::finish()
{
    messageBrowser->setMarkdown(messageCache);
}

void IMessageWidget::appendMessage(const QString &message)
{
    if (message.isEmpty()) return;
    spinner->stop();
    spinner->parentWidget()->close();

    messageCache += message;

    messageBrowser->setMarkdown(messageCache);
    QString html = messageBrowser->toHtml();

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

    messageBrowser->setHtml(html);
}


IChatWidget::IChatWidget(QWidget *parent)
    : IWidget(parent)
    , scrollArea(new QScrollArea(this))
    , chatContainer(new QWidget(this))
    , latestMessageWidget(nullptr)
{
    setupUI();
}

void IChatWidget::setupUI()
{
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    setStyleSheet("background-color: white;");
    setContentsMargins(0, 0, 0, 0);

    auto chatLayout = new QVBoxLayout(chatContainer);
    chatLayout->setContentsMargins(40, 0, 40, 0);
    chatLayout->setSpacing(0);
    chatLayout->setAlignment(Qt::AlignTop);
    chatContainer->setLayout(chatLayout);

    scrollArea->setWidget(chatContainer);
}

void IChatWidget::addMessage(const QString &userName, const QPixmap &avatar, const QString &message)
{
    IMessageWidget* messageWidget = new IMessageWidget(userName, avatar, message, this);
    chatContainer->layout()->addWidget(messageWidget);
    latestMessageWidget = messageWidget;

    QTimer::singleShot(0, this, &IChatWidget::scrollToBottom);
}

bool IChatWidget::isNew()
{
    return latestMessageWidget == nullptr;
}

IMessageWidget* IChatWidget::getLatestMessageWidget() const
{
    return latestMessageWidget;
}

void IChatWidget::scrollToBottom()
{
    scrollArea->verticalScrollBar()->setValue(scrollArea->verticalScrollBar()->maximum());
}
