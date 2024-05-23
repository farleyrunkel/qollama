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
#include "waitingspinnerwidget.h"

class IAutoResizeTextBrowser : public QTextBrowser {
    Q_OBJECT

public:
    IAutoResizeTextBrowser(QWidget* parent = nullptr);

protected:
    void resizeEvent(QResizeEvent* event) override;

public:
    void updateGeometry();
};

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

    void addMessage(const QString& userName, const QPixmap& avatar, const QString& message);

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
