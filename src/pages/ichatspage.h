#ifndef ICHATSPAGE_H
#define ICHATSPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QMenu>
#include <QAction>
#include <QJsonObject>
#include "ilineedit.h"
#include "ichatwidget.h"
#include "iwidget.h"

class IChatsPage : public IWidget
{
    Q_OBJECT

public:
    explicit IChatsPage(QWidget *parent = nullptr);

    IChatWidget* currentChat();

private slots:
    void sendMessage(const QString &text);
    void handleSendMessage();
    void updateMenu(const QList<QString>& list);

private:
    void setupUI();
    IChatWidget* addChat();

    QVBoxLayout* m_mainLayout;
    QStackedWidget* m_chatContainer;
    ILineEdit* m_messageLineEdit;
    QMenu* m_optionMenu;
};

#endif // ICHATSPAGE_H
