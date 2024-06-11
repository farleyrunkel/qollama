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
                    const QString &avatar);
    bool isEmpty() const;
    IMessageBox *getLatestMessageWidget() const;

    QList<IMessageBox*> allMessageBoxes() const {
        return messageBoxes;
    }

    void scrollToBottom();

private:
    void setupMainUI();

private:
    QList<IMessageBox*> messageBoxes;
    QWidget *m_chatContainer;
};

#endif // ICHATSCROLLAREA_H
