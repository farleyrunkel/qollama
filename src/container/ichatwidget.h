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
#include <QPushButton>
#include <QPropertyAnimation>
#include "spinner/waitingspinnerwidget.h"
#include "iautoresizetextbrowser.h"

class IMessageWidget : public QWidget {
    Q_OBJECT

public:
    IMessageWidget(const QString& userName, const QPixmap& avatar, const QString& message, QWidget* parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event);

public:
    void setMarkdown(const QString& markdown );

    void appendMessage(const QString& message);

    void finish();

    void setPixmap(const QPixmap &avatar);

private:
    void setAnimation();
    void setupUI();

private:
    QLabel* avatarLabel;
    QLabel* userLabel;
    IAutoResizeTextBrowser* messageBrowser;
    WaitingSpinnerWidget* spinner;

    QString messageCache;
};


class IChatWidget : public QScrollArea {
    Q_OBJECT

public:
    IChatWidget(QWidget* parent = nullptr);

    void addMessage(const QString& message, const QString& userName, const QPixmap& avatar = QIcon("://icon/ollama.png").pixmap(30));

    bool isNew();

    IMessageWidget* getLatestMessageWidget() const;
    void scrollToBottom();

private:
    void setupUI();

private:
    IMessageWidget* latestMessageWidget;
    QWidget* chatContainer;

};


#endif // ICHATWIDGET_H
