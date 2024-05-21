#ifndef ICHATWIDGET_H
#define ICHATWIDGET_H

#include <QApplication>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QTimer>
#include <QLabel>

class AutoResizingTextEdit : public QTextBrowser {
    Q_OBJECT

public:
    AutoResizingTextEdit(QWidget* parent = nullptr) : QTextBrowser(parent) {
        setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);\
        connect(this, &QTextEdit::textChanged, this, &AutoResizingTextEdit::updateHeight);
        updateHeight();
    }

protected:
    void resizeEvent(QResizeEvent* event) override {
        QTextEdit::resizeEvent(event);
        updateHeight();
    }

private slots:
    void updateHeight() {
        document()->setTextWidth(width()-5);
        setFixedHeight(document()->size().height());
    }

};

class MessageWidget : public QWidget {
    Q_OBJECT

public:
    MessageWidget(const QString& userName, const QPixmap& avatar, const QString& message, QWidget* parent = nullptr)
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
        messageText = new AutoResizingTextEdit(this);
        messageText->setMarkdown(message);

        textLayout->addWidget(userNameLabel);
        textLayout->addWidget(messageText);

        mainLayout->addLayout(avatarLayout);
        mainLayout->addLayout(textLayout);
        setLayout(mainLayout);
    }

    void appendMessage(const QString& message) {
        text += message;
        messageText->setMarkdown(text);
    }

private:
    QString text;
    AutoResizingTextEdit* messageText;
};


class IChatWidget : public QScrollArea {
    Q_OBJECT

public:
    IChatWidget(QWidget* parent = nullptr) : QScrollArea(parent) {
        setWidgetResizable(true);
        latestMessageWidget = nullptr;
        chatContainer = new QWidget(this);
        chatLayout = new QVBoxLayout(chatContainer);
        chatLayout->setAlignment(Qt::AlignTop);
        chatContainer->setLayout(chatLayout);

        setWidget(chatContainer);
    }

    void addMessage(const QString& userName, const QPixmap& avatar, const QString& message) {
        MessageWidget* messageWidget = new MessageWidget(userName, avatar, message, this);
        chatLayout->addWidget(messageWidget);

        latestMessageWidget = messageWidget; // Store the latest message widget
        QTimer::singleShot(0, this, &IChatWidget::scrollToBottom);
    }


    bool isNew() {
        return latestMessageWidget == nullptr;
    }

    MessageWidget* getLatestMessageWidget() const {
        return latestMessageWidget;
    }

public slots:
    void scrollToBottom() {
        verticalScrollBar()->setValue(verticalScrollBar()->maximum());
    }

private:
    MessageWidget* latestMessageWidget;
    QWidget* chatContainer;
    QVBoxLayout* chatLayout;
};



#endif // ICHATWIDGET_H
