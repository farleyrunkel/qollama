#include "ichatspage.h"
#include "configmanager.h"
#include "signalhub.h"
#include "stylemanager.h"

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

    m_chatsStack = new QStackedWidget;

    m_bottomLayout = new QHBoxLayout;

    m_mainLayout->addWidget(m_topArea);
    m_mainLayout->addWidget(m_chatsStack);
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

    connect(&ConfigManager::instance(), &ConfigManager::onAvatarChanged,
            m_userButton, [this]() {
                QPixmap avatar(
                    ConfigManager::instance().config("avatar").toString());
                m_userButton->setIcon(QIcon(StyleManager::roundedPixmap(avatar)));
            });

    connect(&SignalHub::instance(), &SignalHub::onSideAreaHidden, m_expandButton,
            &QPushButton::setVisible);
    connect(&SignalHub::instance(), &SignalHub::onSideAreaHidden, m_newChatButton,
            &QPushButton::setVisible);
    connect(m_expandButton, &QPushButton::clicked, &SignalHub::instance(),
            &SignalHub::onExpandButtonClicked);
    connect(m_newChatButton, &QPushButton::clicked, &SignalHub::instance(),
            &SignalHub::onNewChatButtonClicked);
    connect(m_userButton, &QPushButton::clicked, &SignalHub::instance(),
            &SignalHub::onUserButtonClicked);
    connect(m_langButton, &QPushButton::clicked, this, [this]() {
        m_langButton->setText(m_langButton->text() == "cn" ? "en" : "cn");
    });
}

void IChatsPage::setupTopArea() {
    // Set up the top area of the chats page
    auto topAreaLayout = new QHBoxLayout(m_topArea);
    topAreaLayout->setContentsMargins(0, 0, 0, 0);

    m_expandButton = new QPushButton(QIcon("://icon/sidebar-left.svg"), "");
    m_expandButton->setObjectName("smallButton");

    m_newChatButton = new QPushButton(QIcon(":/icon/create-new.svg"), "");
    m_newChatButton->setObjectName("smallButton");

    QPixmap avatar(ConfigManager::instance().config("avatar").toString());
    m_userButton =
        new QPushButton(QIcon(StyleManager::roundedPixmap(avatar)), "");
    m_userButton->setObjectName("smallButton");

    m_langButton = new QPushButton("en");
    m_langButton->setObjectName("smallButton");

    m_expandButton->hide();
    m_newChatButton->hide();

    m_topStack = new QStackedWidget;
    m_topLabel = new QLabel("llama3");
    m_topStack->addWidget(m_topLabel);
    m_topStack->setCurrentWidget(m_topLabel);

    topAreaLayout->addWidget(m_expandButton);
    topAreaLayout->addWidget(m_newChatButton);
    topAreaLayout->addWidget(m_topStack);
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

    IChatScrollArea *chat = currentChat();

    if (isNewChat || !chat) {
        chat = addChat();
    }

    chat->addMessage(text, ConfigManager::instance().username(),
                     ConfigManager::instance().config("avatar").toString());
    chat->addMessage("", "llama3");

    QJsonObject json;
    json["prompt"] =
        QString(m_langButton->text() == "cn" ? "请用中文回答\n"
                                                          : "Please answer in english.\n") +
                     text;
    json["model"] = "llama3";

    emit SignalHub::instance().onMessageAdded(text);
    emit SignalHub::instance().generateRequest(json);
}

void IChatsPage::handleSendMessage() {
    // Handle sending a message in the chat area
    QString text = m_messageLineEdit->text();
    sendMessage(text);
    m_messageLineEdit->clear();
}

QPushButton *IChatsPage::expandButton() const { return m_expandButton; }

IChatScrollArea *IChatsPage::addChat() {
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
