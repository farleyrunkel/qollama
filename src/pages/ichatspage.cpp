#include "ichatspage.h"
#include "signalhub.h"
#include "configmanager.h"

IChatsPage::IChatsPage(QWidget *parent) : IWidget(parent)
{
    setupUI();

    connect(&SignalHub::instance(), &SignalHub::on_message_sent, this, &IChatsPage::sendMessage);
    connect(m_messageLineEdit->rightButton(), &QPushButton::clicked, this, &IChatsPage::handleSendMessage);
    connect(m_messageLineEdit, &ILineEdit::returnPressed, this, &IChatsPage::handleSendMessage);
    connect(&SignalHub::instance(), &SignalHub::listReceived, this, &IChatsPage::updateMenu);
}

void IChatsPage::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    m_chatContainer = new QStackedWidget(this);
    m_messageLineEdit = new ILineEdit(this);
    m_messageLineEdit->setPlaceholderText("Message llama3 ...");

    auto sendButton = m_messageLineEdit->rightButton();
    sendButton->setIcon(QIcon(":/icon/send.svg"));

    auto optionButton = m_messageLineEdit->leftButton();
    optionButton->setIcon(QIcon(":/icon/more-horiz.svg"));

    m_optionMenu = new QMenu(this);
    optionButton->setMenu(m_optionMenu);

    m_mainLayout->addWidget(m_chatContainer);
    m_mainLayout->addWidget(m_messageLineEdit);
}

void IChatsPage::sendMessage(const QString &text)
{
    if (text.isEmpty()) return;

    IChatWidget* chat = currentChat();
    if (!chat) {
        chat = addChat();
    }

    chat->addMessage(text, ConfigManager::instance().username(), ConfigManager::instance().avatar());
    chat->addMessage("", "llama3");

    QJsonObject json;
    json["prompt"] = text;
    json["model"] = "llama3";
    emit SignalHub::instance().generateRequest(json);
}

void IChatsPage::handleSendMessage()
{
    QString text = m_messageLineEdit->text();
    sendMessage(text);
    m_messageLineEdit->clear();
}

IChatWidget* IChatsPage::addChat()
{
    IChatWidget* chat = new IChatWidget(this);
    m_chatContainer->addWidget(chat);
    emit SignalHub::instance().newChatAdded(m_chatContainer->count());
    return chat;
}

IChatWidget* IChatsPage::currentChat()
{
    return qobject_cast<IChatWidget*>(m_chatContainer->currentWidget());
}

void IChatsPage::updateMenu(const QList<QString>& list)
{
    m_optionMenu->clear();
    for (const QString& item : list) {
        QAction* action = new QAction(item, this);
        m_optionMenu->addAction(action);
        connect(action, &QAction::triggered, this, [this, action]() {
            m_messageLineEdit->setPlaceholderText("Message " + action->text() + " ...");
        });
    }
}
