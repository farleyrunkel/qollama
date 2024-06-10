#ifndef ICHATSCROLLAREA_H
#define ICHATSCROLLAREA_H

#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

#include "imessagebox.h"

class IChatScrollArea : public QScrollArea {
    Q_OBJECT

public:
    IChatScrollArea(QWidget *parent = nullptr);

    void addMessage(const QString &message, const QString &userName,
                    const QString &avatar = "://icons/ollama.png");
    bool isNew() const;
    IMessageBox *getLatestMessageWidget() const;
    void scrollToBottom();

private:
    void setupUI();

private:
    IMessageBox *m_latestMessageWidget;
    QWidget *m_chatContainer;
};

#endif // ICHATSCROLLAREA_H
