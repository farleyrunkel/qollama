#ifndef ICHATSPAGE_H
#define ICHATSPAGE_H

#include "ichatscrollarea.h"
#include "ilineedit.h"
#include "iwidget.h"
#include <QHBoxLayout>
#include <QMenu>
#include <QToolButton>
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
    QStackedWidget *chats() const;
    IChatScrollArea *currentChat();

    void appendWordToActiveChat(QString text);

private slots:
    void toSendMessage(const QString &text, bool isNewChat = false);
    void toHandleMessage();
    void toUpdateMenu(const QList<QString> &list);
    void onOllamaFinished();

private:
    void setupMainUi(QWidget* widget);
    void setupTopArea(QWidget* widget);
    void setupChatArea(QStackedWidget* widget);
    void setupBottomArea(QHBoxLayout* layout);
    void setupConnections();

    IChatScrollArea *addNewChat();

private:
    QVBoxLayout *m_mainLayout;
    QWidget *m_topArea;
    QStackedWidget *m_chatsStack;
    QHBoxLayout *m_bottomLayout;
    ILineEdit *m_messageLineEdit;

    QPushButton *m_expandButton;
    QPushButton *m_newChatButton;
    QPushButton *m_userButton;
    QPushButton *m_langButton;

    QMenu *m_optionMenu;

    QToolButton* m_topLabel;
    QStackedWidget* m_topStack;
};

#endif // ICHATSPAGE_H
