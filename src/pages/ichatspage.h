#ifndef ICHATSPAGE_H
#define ICHATSPAGE_H

#include "ichatscrollarea.h"
#include "ilineedit.h"
#include "iwidget.h"
#include <QHBoxLayout>
#include <QMenu>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>

/**
 * @brief The IChatsPage class represents a page for displaying chats.
 * It includes functionality for sending messages, managing chats, and updating
 * the UI.
 */
class IChatsPage : public IWidget {
    Q_OBJECT

public:
    explicit IChatsPage(QWidget *parent = nullptr);
    QPushButton *expandButton() const;
    QStackedWidget *chats() const;
    IChatScrollArea *currentChat();

private slots:
    void sendMessage(const QString &text, bool isNewChat = false);
    void handleSendMessage();
    void updateMenu(const QList<QString> &list);

private:
    void setupMainLayout();
    void setupTopArea();
    void setupChatArea();
    void setupBottomArea();
    void setupConnections();

    IChatScrollArea *addChat();
    QPushButton *createButton(const QString &iconPath);

private:
    QVBoxLayout *m_mainLayout;
    QWidget *m_topArea;
    QStackedWidget *m_chatsStack;
    QHBoxLayout *m_bottomLayout;
    ILineEdit *m_messageLineEdit;
    QPushButton *m_expandButton;
    QPushButton *m_newChatButton;
    QPushButton *m_userButton;
    QMenu *m_optionMenu;
};

#endif // ICHATSPAGE_H
