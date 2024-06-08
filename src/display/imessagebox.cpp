#include "imessagebox.h"

#include "stylemanager.h"
#include <QColor>
#include <QFont>
#include <QFrame>
#include <QHBoxLayout>
#include <QResizeEvent>
#include <QVBoxLayout>

IMessageBox::IMessageBox(const QString &userName, const QString &avatar,
                         const QString &message, QWidget *parent)
    : QWidget(parent), avatarLabel(new QLabel(this)),
    userLabel(new QLabel(userName, this)),
    messageBrowser(new IAutoResizeTextBrowser(this)), spinner(nullptr),
    messageCache() {
    setupUI();
    setAvatar(avatar);
    setAnimation();
    appendMessage(message);
    finish();
}

void IMessageBox::setAvatar(const QString &avatar) {
    auto m_avatar = StyleManager::roundedPixmap(QPixmap(avatar));

    avatarLabel->setPixmap(QPixmap(avatar).scaled(avatarLabel->size()));
}

void IMessageBox::setupUI() {
    // Setting up the main layout
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    setLayout(mainLayout);

    // Setting up the avatar layout
    QVBoxLayout *avatarLayout = new QVBoxLayout();
    avatarLayout->setAlignment(Qt::AlignTop);

    int borderWidth = 1;
    avatarLabel->setFixedSize(QSize(31, 31));
    // avatarLabel->setStyleSheet(
    //     QString("border: %1px solid black; border-radius: %2px; padding: %3px; text-align: center;")
    //         .arg(1)
    //         .arg((avatarLabel->width() - borderWidth) / 2)
    //         .arg(borderWidth));
    avatarLayout->addWidget(avatarLabel);

    // Setting up the text layout
    QVBoxLayout *textLayout = new QVBoxLayout();
    userLabel->setFont(QFont("Yahei", 10, QFont::Bold));
    textLayout->addWidget(userLabel);
    textLayout->addWidget(messageBrowser);

    // Adding layouts to the main layout
    mainLayout->addLayout(avatarLayout, 0);
    mainLayout->addLayout(textLayout, 1);
}

void IMessageBox::setAnimation() {
    // Setting up the spinner animation
    QFrame *spinFrame = new QFrame(this);
    spinFrame->setFixedSize(QSize(20, 20));
    QVBoxLayout *layout = new QVBoxLayout(spinFrame);
    spinner = new WaitingSpinnerWidget(spinFrame);

    // Configuring the spinner properties
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

    spinner->start();
}

void IMessageBox::resizeEvent(QResizeEvent *event) {
    // Handling resize events to adjust spinner position
    QWidget::resizeEvent(event);
    spinner->parentWidget()->setGeometry(messageBrowser->geometry());
}

void IMessageBox::setMarkdown(const QString &markdown) {
    // Setting markdown content in the message browser
    messageBrowser->setMarkdown(markdown);
}

void IMessageBox::finish() {
    // Finalizing the message display
    messageBrowser->setMarkdown(messageCache);
}

void IMessageBox::appendMessage(const QString &message) {
    // Appending new message to the message browser
    if (message.isEmpty())
        return;

    // Stopping and hiding the spinner
    spinner->stop();
    spinner->parentWidget()->close();

    // Caching and displaying the message
    messageCache += message;
    messageBrowser->setMarkdown(messageCache);
    QString html = messageBrowser->toHtml();

    // Adding a custom image to the HTML content
    QString circleSpan =
        "<img src=':/icon/qtcircle.svg' height='11' width='11'/>";

    if (html.contains("</p></body></html>")) {
        html.replace("</p></body></html>", circleSpan + "</p></body></html>");
    } else if (html.contains("</li></ol></body></html>")) {
        html.replace("</li></ol></body></html>",
                     circleSpan + "</li></ol></body></html>");
    } else if (html.contains("</li></ul></body></html>")) {
        html.replace("</li></ul></body></html>",
                     circleSpan + "</li></ul></body></html>");
    }

    // Setting the updated HTML content
    messageBrowser->setHtml(html);
}
