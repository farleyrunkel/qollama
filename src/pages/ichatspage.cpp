#include "ichatspage.h"
#include "isignalhub.h"
#include "iconfigmanager.h"

IChatsPage::IChatsPage(QWidget *parent) : IWidget(parent)
{
    setupUI();
    auto signalHub = &ISignalHub::instance();

    connect(signalHub, &ISignalHub::on_IVPushCard_clicked, this, &IChatsPage::sendMessage);
    connect(m_messageLineEdit->rightButton(), &QPushButton::clicked, this, &IChatsPage::handleSendMessage);
    connect(m_messageLineEdit, &ILineEdit::returnPressed, this, &IChatsPage::handleSendMessage);
    connect(signalHub, &ISignalHub::listReceived, this, &IChatsPage::updateMenu);
}

void IChatsPage::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    m_chatContainer = new QStackedWidget(this);
    m_messageLineEdit = new ILineEdit(this);

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

    chat->addMessage(text, IConfigManager::instance().getUsername(), IConfigManager::instance().getAvatar());
    chat->addMessage("", "llama3");

    QJsonObject json;
    json["prompt"] = text;
    json["model"] = "llama3";
    emit ISignalHub::instance().generateRequest(json);
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
    emit ISignalHub::instance().newChatAdded(m_chatContainer->count());
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
