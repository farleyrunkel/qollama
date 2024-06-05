#include "ichatspage.h"
#include "signalhub.h"
#include "configmanager.h"

IChatsPage::IChatsPage(QWidget *parent) : IWidget(parent)
{
    m_mainLayout = new QVBoxLayout(this);

    setupTitleBar();
    setupChatComponents();

    connect(&SignalHub::instance(), &SignalHub::on_message_sent, this, &IChatsPage::sendMessage);
    connect(m_messageLineEdit->rightButton(), &QPushButton::clicked, this, &IChatsPage::handleSendMessage);
    connect(m_messageLineEdit, &ILineEdit::returnPressed, this, &IChatsPage::handleSendMessage);
    connect(&SignalHub::instance(), &SignalHub::listReceived, this, &IChatsPage::updateMenu);
}

void IChatsPage::setupTitleBar()
{
    auto titleBar = new QWidget(this);
    titleBar->setFixedHeight(35);

    auto titleLayout = new QHBoxLayout(titleBar);
    titleLayout->setContentsMargins(0, 0, 0, 0);

    m_expandButton = new QPushButton;
    m_expandButton->setIcon(QIcon("://icon/sidebar-left.svg"));
    m_expandButton->setFixedSize(QSize(30, 30));
    m_expandButton->setObjectName("smallButton");
    m_expandButton->hide();

    m_userButton = new QPushButton;
    m_userButton->setIcon(QIcon("://icon.png"));
    m_userButton->setFixedSize(QSize(30, 30));
    m_userButton->setObjectName("smallButton");

    titleLayout->addWidget(m_expandButton);
    titleLayout->addStretch();
    titleLayout->addWidget(m_userButton);

    m_mainLayout->addWidget(titleBar);
}

void IChatsPage::setupChatComponents()
{
    m_chatContainer = new QStackedWidget(this);
    m_messageLineEdit = new ILineEdit(this);
    m_messageLineEdit->setPlaceholderText("Message llama3 ...");
    m_messageLineEdit->setFixedHeight(40);
    auto sendButton = m_messageLineEdit->rightButton();
    sendButton->setIcon(QIcon(":/icon/send.svg"));

    auto optionButton = m_messageLineEdit->leftButton();
    optionButton->setIcon(QIcon(":/icon/more-horiz.svg"));

    m_optionMenu = new QMenu(this);
    optionButton->setMenu(m_optionMenu);

    m_mainLayout->addWidget(m_chatContainer);
    m_mainLayout->addWidget(m_messageLineEdit);
}

void IChatsPage::sendMessage(const QString &text, bool isNewChat)
{
    if (text.isEmpty()) return;

    IChatWidget* chat = currentChat();

    if (isNewChat || !chat) {
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

QPushButton* IChatsPage::expandButton() const
{
    return m_expandButton;
}

IChatWidget* IChatsPage::addChat()
{
    IChatWidget* chat = new IChatWidget(this);
    m_chatContainer->addWidget(chat);
    m_chatContainer->setCurrentWidget(chat);
    qDebug() << "add new chat: " << m_chatContainer->indexOf(chat);
    emit SignalHub::instance().newChatAdded(chat);
    return chat;
}

IChatWidget* IChatsPage::currentChat()
{
    return qobject_cast<IChatWidget*>(m_chatContainer->currentWidget());
}

QStackedWidget *IChatsPage::chats() const { return m_chatContainer; }

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
