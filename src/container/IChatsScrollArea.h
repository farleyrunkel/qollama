#ifndef ICHATWIDGET_H
#define ICHATWIDGET_H

#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

#include "imessagebox.h"

class IChatsScrollArea : public QScrollArea {
    Q_OBJECT

public:
    IChatsScrollArea(QWidget* parent = nullptr);

    void addMessage(const QString& message, const QString& userName, const QPixmap& avatar = QPixmap("://icon/ollama.png"));
    bool isNew() const;
    IMessageBox* getLatestMessageWidget() const;
    void scrollToBottom();

private:
    void setupUI();

private:
    IMessageBox* m_latestMessageWidget;
    QWidget* m_chatContainer;
};

#endif // ICHATWIDGET_H
