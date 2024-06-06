#ifndef ICHATSPAGE_H
#define ICHATSPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QMenu>
#include "iwidget.h"
#include "ichatwidget.h"
#include "ilineedit.h"

/**
 * @brief The IChatsPage class represents a page for displaying chats.
 * It includes functionality for sending messages, managing chats, and updating the UI.
 */
class IChatsPage : public IWidget
{
    Q_OBJECT

public:
    explicit IChatsPage(QWidget *parent = nullptr);
    QPushButton* expandButton() const;
    QStackedWidget* chats() const;
    IChatWidget* currentChat();

private slots:
    void sendMessage(const QString& text, bool isNewChat = false);
    void handleSendMessage();
    void updateMenu(const QList<QString>& list);

private:
    void setupMainLayout();
    void setupTopArea();
    void setupChatArea();
    void setupBottomArea();
    void setupConnections();

    IChatWidget* addChat();
    QPushButton* createButton(const QString& iconPath);

private:
    QVBoxLayout* m_mainLayout;
    QWidget* m_topArea;
    QStackedWidget* m_chatsLayout;
    QHBoxLayout* m_bottomLayout;
    ILineEdit* m_messageLineEdit;
    QPushButton* m_expandButton;
    QPushButton* m_newChatButton;
    QPushButton* m_userButton;
    QMenu* m_optionMenu;
};

#endif // ICHATSPAGE_H
