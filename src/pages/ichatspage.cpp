#include "ichatspage.h"
#include "configmanager.h"
#include "signalhub.h"

IChatsPage::IChatsPage(QWidget *parent) : IWidget(parent) {
    // Setup the main layout and all components
    setupMainLayout();
    setupTopArea();
    setupChatArea();
    setupBottomArea();
    setupConnections();
}

void IChatsPage::setupMainLayout() {
    // Set up the main layout of the chats page
    setObjectName("IChatsPage");
    setContentsMargins(0, 0, 0, 0);

    m_mainLayout = new QVBoxLayout(this);
    setLayout(m_mainLayout);

    m_topArea = new QWidget(this);
    m_topArea->setFixedHeight(35);

    m_chatsLayout = new QStackedWidget;

    m_bottomLayout = new QHBoxLayout;

    m_mainLayout->addWidget(m_topArea);
    m_mainLayout->addWidget(m_chatsLayout);
    m_mainLayout->addLayout(m_bottomLayout);
}

void IChatsPage::setupConnections() {
    // Connect signals and slots for interaction
    connect(&SignalHub::instance(), &SignalHub::on_message_sent, this,
            &IChatsPage::sendMessage);
    connect(m_messageLineEdit->rightButton(), &QPushButton::clicked, this,
            &IChatsPage::handleSendMessage);
    connect(m_messageLineEdit, &ILineEdit::returnPressed, this,
            &IChatsPage::handleSendMessage);
    connect(&SignalHub::instance(), &SignalHub::listReceived, this,
            &IChatsPage::updateMenu);

    connect(m_expandButton, &QPushButton::clicked, &SignalHub::instance(),
            &SignalHub::onExpandButtonClicked);
    connect(&SignalHub::instance(), &SignalHub::onSideAreaHidden, m_expandButton,
            &QPushButton::setVisible);
    connect(&SignalHub::instance(), &SignalHub::onSideAreaHidden, m_newChatButton,
            &QPushButton::setVisible);
    connect(&SignalHub::instance(), &SignalHub::onSideAreaHidden, m_userButton,
            &QPushButton::setVisible);
}

void IChatsPage::setupTopArea() {
    // Set up the top area of the chats page
    auto topAreaLayout = new QHBoxLayout(m_topArea);
    topAreaLayout->setContentsMargins(0, 0, 0, 0);

    m_expandButton = createButton("://icon/sidebar-left.svg");
    m_newChatButton = createButton(":/icon/create-new.svg");
    m_userButton = createButton("://icon.png");

    m_expandButton->hide();
    m_newChatButton->hide();
    m_userButton->hide();

    topAreaLayout->addWidget(m_expandButton);
    topAreaLayout->addWidget(m_newChatButton);
    topAreaLayout->addStretch(1);
    topAreaLayout->addWidget(m_userButton);
}

void IChatsPage::setupChatArea() {
    // Set up the chat area of the chats page
    // Not implemented in this snippet
}

void IChatsPage::setupBottomArea() {
    // Set up the bottom area of the chats page
    m_messageLineEdit = new ILineEdit(this);
    m_messageLineEdit->setPlaceholderText("Message llama3 ...");
    m_messageLineEdit->setFixedHeight(40);
    auto sendButton = m_messageLineEdit->rightButton();
    sendButton->setIcon(QIcon(":/icon/send.svg"));

    auto optionButton = m_messageLineEdit->leftButton();
    optionButton->setIcon(QIcon(":/icon/more-horiz.svg"));

    m_optionMenu = new QMenu(this);
    optionButton->setMenu(m_optionMenu);

    m_bottomLayout->addWidget(m_messageLineEdit);
}

void IChatsPage::sendMessage(const QString &text, bool isNewChat) {
    // Send a message in the chat area
    if (text.isEmpty())
        return;

    IChatWidget *chat = currentChat();

    if (isNewChat || !chat) {
        chat = addChat();
    }

    chat->addMessage(text, ConfigManager::instance().username(),
                     ConfigManager::instance().avatar());
    chat->addMessage("", "llama3");

    QJsonObject json;
    json["prompt"] = text;
    json["model"] = "llama3";
    emit SignalHub::instance().generateRequest(json);
}

void IChatsPage::handleSendMessage() {
    // Handle sending a message in the chat area
    QString text = m_messageLineEdit->text();
    sendMessage(text);
    m_messageLineEdit->clear();
}

QPushButton *IChatsPage::expandButton() const { return m_expandButton; }

IChatWidget *IChatsPage::addChat() {
    // Add a new chat widget
    IChatWidget *chat = new IChatWidget;
    m_chatsLayout->addWidget(chat);
    m_chatsLayout->setCurrentWidget(chat);
    qDebug() << "add new chat: " << m_chatsLayout->indexOf(chat);
    emit SignalHub::instance().newChatAdded(chat);
    return chat;
}

IChatWidget *IChatsPage::currentChat() {
    // Get the current active chat widget
    return qobject_cast<IChatWidget *>(m_chatsLayout->currentWidget());
}

QStackedWidget *IChatsPage::chats() const {
    // Get the chat area layout
    return m_chatsLayout;
}

void IChatsPage::updateMenu(const QList<QString> &list) {
    // Update the menu options
    m_optionMenu->clear();
    for (const QString &item : list) {
        QAction *action = new QAction(item, this);
        m_optionMenu->addAction(action);
        connect(action, &QAction::triggered, this, [this, action]() {
            m_messageLineEdit->setPlaceholderText("Message " + action->text() +
                                                  " ...");
        });
    }
}

QPushButton *IChatsPage::createButton(const QString &iconPath) {
    // Create a button with an icon
    auto button = new QPushButton;
    button->setIcon(QIcon(iconPath));
    button->setFixedSize(QSize(30, 30));
    button->setObjectName("smallButton");
    return button;
}
