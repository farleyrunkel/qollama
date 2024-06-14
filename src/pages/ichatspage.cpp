#include "ichatspage.h"
#include "client.h"
#include "configmanager.h"
#include "signalhub.h"
#include "stylemanager.h"
#include <QJsonArray>

IChatsPage::IChatsPage(QWidget *parent) : IWidget(parent) {
    // Setup the main layout and all components
    setupMainUi();
    setupTopArea();
    setupChatArea();
    setupBottomArea();
    setupConnections();
}

void IChatsPage::setupMainUi() {
    // Set up the main layout of the chats page
    setObjectName("iChatsPage");
    setContentsMargins(0, 0, 0, 0);

    m_mainLayout = new QVBoxLayout(this);
    setLayout(m_mainLayout);

    m_topArea = new QWidget(this);
    m_topArea->setFixedHeight(35);

    m_chatsStack = new QStackedWidget;

    m_bottomLayout = new QHBoxLayout;

    m_mainLayout->addWidget(m_topArea);
    m_mainLayout->addWidget(m_chatsStack);
    m_mainLayout->addLayout(m_bottomLayout);
}

void IChatsPage::setupConnections() {

    connect(m_expandButton, &QPushButton::clicked, &SignalHub::instance(),
            &SignalHub::onExpandButtonClicked);
    connect(m_newChatButton, &QPushButton::clicked, &SignalHub::instance(),
            &SignalHub::onNewChatButtonClicked);
    connect(m_userButton, &QPushButton::clicked, &SignalHub::instance(),
            &SignalHub::onUserButtonClicked);
    connect(m_langButton, &QPushButton::clicked, this, [this]() {
        m_langButton->setText(m_langButton->text() == "cn" ? "en" : "cn");
    });
    connect(m_messageLineEdit->rightButton(), &QPushButton::clicked, this,
            &IChatsPage::handleSendMessage);
    connect(m_messageLineEdit, &ILineEdit::returnPressed, this,
            &IChatsPage::handleSendMessage);

    connect(&SignalHub::instance(), &SignalHub::listReceived, this,
            &IChatsPage::updateMenu);
    connect(&SignalHub::instance(), &SignalHub::on_message_sent, this,
            &IChatsPage::sendMessage);
    connect(&SignalHub::instance(), &SignalHub::onSideAreaHidden, m_expandButton,
            &QPushButton::setVisible);
    connect(&SignalHub::instance(), &SignalHub::onSideAreaHidden, m_newChatButton,
            &QPushButton::setVisible);

    connect(&ConfigManager::instance(), &ConfigManager::onAvatarChanged,
            m_userButton, [this]() {
        QPixmap avatar(
            ConfigManager::instance().config("avatar").toString());
        m_userButton->setIcon(QIcon(StyleManager::roundedPixmap(avatar)));
    });

    connect(&ollama::Client::instance(), &ollama::Client::replyReceived, this,
            &IChatsPage::appendWordToActiveChat);
    connect(&ollama::Client::instance(), &ollama::Client::finished, this,
            &IChatsPage::onOllamaFinished);
}

void IChatsPage::setupTopArea() {
    // Set up the top area of the chats page
    auto topAreaLayout = new QHBoxLayout(m_topArea);
    topAreaLayout->setContentsMargins(0, 0, 0, 0);

    m_expandButton = new QPushButton(QIcon("://icons/sidebar-left.svg"), "");
    m_expandButton->setObjectName("smallButton");

    m_newChatButton = new QPushButton(QIcon(":/icons/create-new.svg"), "");
    m_newChatButton->setObjectName("smallButton");

    QPixmap avatar(ConfigManager::instance().config("avatar").toString());
    m_userButton =
        new QPushButton(QIcon(StyleManager::roundedPixmap(avatar)), "");
    m_userButton->setObjectName("smallButton");

    m_langButton = new QPushButton("en");
    m_langButton->setObjectName("smallButton");

    m_expandButton->hide();
    m_newChatButton->hide();

    m_topLabel = new QToolButton;
    m_topLabel->setText("llama3");
    m_topLabel->setObjectName("bigButton");

    topAreaLayout->addWidget(m_expandButton);
    topAreaLayout->addWidget(m_newChatButton);
    topAreaLayout->addWidget(m_topLabel);
    topAreaLayout->addStretch(1);
    topAreaLayout->addWidget(m_langButton);
    topAreaLayout->addWidget(m_userButton);
}

void IChatsPage::setupChatArea() {
    // Set up the chat area of the chats page
    // Not implemented in this snippet

    // m_chatsStack->setFrameShape(QFrame::NoFrame);
    m_chatsStack->setStyleSheet("border: red;");
}

void IChatsPage::setupBottomArea() {
    // Set up the bottom area of the chats page
    m_messageLineEdit = new ILineEdit(this);
    m_messageLineEdit->setPlaceholderText("Message llama3 ...");
    m_messageLineEdit->setFixedHeight(40);
    auto sendButton = m_messageLineEdit->rightButton();

    QIcon icon;
    icon.addPixmap(QPixmap(":/icons/send.svg"), QIcon::Normal);
    icon.addPixmap(QPixmap(":/icons/send.svg"), QIcon::Disabled);
    icon.addPixmap(QPixmap(":/icons/stop.svg"), QIcon::Active);

    sendButton->setIcon(icon);

    auto optionButton = m_messageLineEdit->leftButton();
    optionButton->setIcon(QIcon(":/icons/more-horiz.svg"));

    m_optionMenu = new QMenu(this);
    optionButton->setMenu(m_optionMenu);

    m_bottomLayout->addWidget(m_messageLineEdit);
}

void IChatsPage::sendMessage(const QString &text, bool isNewChat) {
    // Send a message in the chat area
    if (text.isEmpty())
        return;

    IChatScrollArea *chat = currentChat();

    if (isNewChat || !chat) {
        chat = addNewChat();
    }

    chat->addMessage(text, ConfigManager::instance().username(),
                     ConfigManager::instance().config("avatar").toString());
    chat->addMessage("", "llama3", "://images/ollama.png");



    // fresh main ui and add new history list item in left side area.
    emit SignalHub::instance().onMessageAdded(text);

    QJsonObject json;
    QJsonArray messages;

    for (auto *a : chat->allMessageBoxes()) {
        QJsonObject message;
        message["role"] = a->role();
        message["content"] = a->message();
        messages.append(message);
    }

    json["messages"] = messages;
    json["model"] = "llama3";

    // send message to ollama client
    emit SignalHub::instance().chatRequest(json);
}

void IChatsPage::onOllamaFinished() {
    auto *chatListView = currentChat();
    if (!chatListView) {
        qDebug() << "Current chat list is null.";
        return;
    }

    IMessageBox *curr = chatListView->getLatestMessageWidget();
    curr->finish();
}

void IChatsPage::appendWordToActiveChat(QString text) {
    auto chatListView = currentChat();
    if (!chatListView) {
        qDebug() << "Current chat list is null.";
        return;
    }

    IMessageBox *curr = chatListView->getLatestMessageWidget();
    curr->appendMessage(text);

    chatListView->scrollToBottom();
}

void IChatsPage::handleSendMessage() {
    // Handle sending a message in the chat area
    QString text = m_messageLineEdit->text();
    sendMessage(text);
    m_messageLineEdit->clear();
}

QPushButton *IChatsPage::expandButton() const { return m_expandButton; }

IChatScrollArea *IChatsPage::addNewChat() {
    // Add a new chat widget
    IChatScrollArea *chat = new IChatScrollArea;
    m_chatsStack->addWidget(chat);
    m_chatsStack->setCurrentWidget(chat);
    qDebug() << "add new chat: " << m_chatsStack->indexOf(chat);
    emit SignalHub::instance().newChatAdded(chat);
    return chat;
}

IChatScrollArea *IChatsPage::currentChat() {
    // Get the current active chat widget
    return qobject_cast<IChatScrollArea *>(m_chatsStack->currentWidget());
}

QStackedWidget *IChatsPage::chats() const {
    // Get the chat area layout
    return m_chatsStack;
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
