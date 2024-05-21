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

class IAutoResizeTextBrowser : public QTextBrowser {
    Q_OBJECT

public:
    IAutoResizeTextBrowser(QWidget* parent = nullptr);

protected:
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void updateHeight();

};

class IMessageWidget : public QFrame {
    Q_OBJECT

public:
    IMessageWidget(const QString& userName, const QPixmap& avatar, const QString& message, QWidget* parent = nullptr);

    void appendMessage(const QString& message);

private:
    QString text;
    IAutoResizeTextBrowser* messageText;
};


class IChatWidget : public QScrollArea {
    Q_OBJECT

public:
    IChatWidget(QWidget* parent = nullptr);

    void addMessage(const QString& userName, const QPixmap& avatar, const QString& message);


    bool isNew();

    IMessageWidget* getLatestMessageWidget() const;

public slots:
    void scrollToBottom();

private:
    IMessageWidget* latestMessageWidget;
    QWidget* chatContainer;
    QVBoxLayout* chatLayout;
};



#endif // ICHATWIDGET_H
