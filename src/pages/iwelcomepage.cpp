#include "iwelcomepage.h"
#include "configmanager.h"
#include "signalhub.h"
#include "stylemanager.h"
#include <QLCDNumber>
#include <QMenu>
#include <QMouseEvent>
#include <QScopedPointer>
#include <QSpacerItem>
#include <QStackedLayout>

IWelcomePage::IWelcomePage(QWidget *parent) : IWidget(parent) {
    setupMainLayout();
    setupTopArea();
    setupContentArea();
    setupConnections();
    retranslateUi();
}

void IWelcomePage::setupMainLayout() {
    setObjectName("IWelcomePage");
    setContentsMargins(0, 0, 0, 0);

    m_mainLayout = new QVBoxLayout(this);

    m_topArea = new QWidget(this);
    m_topArea->setFixedHeight(35);

    m_contentLayout = new QGridLayout;
    m_contentLayout->setHorizontalSpacing(20);
    m_contentLayout->setVerticalSpacing(40);
    m_contentLayout->setContentsMargins(40, 0, 40, 0);

    m_mainLayout->addWidget(m_topArea);
    m_mainLayout->addLayout(m_contentLayout);

    emit SignalHub::instance().listRequest();
}

void IWelcomePage::setupTopArea() {
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

    m_expandButton->hide();
    m_newChatButton->hide();

    topAreaLayout->addWidget(m_expandButton);
    topAreaLayout->addWidget(m_newChatButton);
    topAreaLayout->addStretch(1);
    topAreaLayout->addWidget(m_userButton);
}

void IWelcomePage::setupContentArea() {
    setupContentCards();
    setupContentLabel();
    setupContentLineEdit();
}

void IWelcomePage::setupContentCards() {
    m_card1 = createPushCard("Why the sky is blue?", "://icons/heart-balloon.svg");
    m_card2 =
        createPushCard("Create a personal webpage for me, all in a single file. "
                             "Ask me 3 questions first on whatever you need to know.",
                             "://icons/art-palette.svg");
    m_card3 = createPushCard("Write a short-and-sweet text message inviting my "
                             "neighbor to a barbecue.",
                             "://icons/electric-light-bulb.svg");
    m_card4 = createPushCard("Tell me a random fun fact about the Roman Empire",
                             "://icons/terminal.svg");

    m_contentLayout->addWidget(m_card1, 1, 1, 1, 1);
    m_contentLayout->addWidget(m_card2, 1, 2, 1, 1);
    m_contentLayout->addWidget(m_card3, 2, 1, 1, 1);
    m_contentLayout->addWidget(m_card4, 2, 2, 1, 1);
}

IVPushCard *IWelcomePage::createPushCard(const QString &text,
                                         const QString &iconPath) {
    auto card = new IVPushCard;
    card->setText(text);
    card->setPixmap(QPixmap(iconPath));
    return card;
}

void IWelcomePage::setupContentLabel() {
    m_welcomeLogo = new QLabel;
    m_welcomeLogo->setObjectName("welcomeLogo");
    m_welcomeLogo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_welcomeLogo->setMinimumSize(QSize(200, 70));
    m_welcomeLogo->setMaximumSize(QSize(4000, 100));
    m_welcomeLogo->setStyleSheet("image: url(://images/qollama-logo-name.png);");
    m_welcomeLogo->setAlignment(Qt::AlignCenter);

    m_contentLayout->addWidget(m_welcomeLogo, 0, 1, 1, 2);
}

void IWelcomePage::setupContentLineEdit() {
    m_inputLine = new ILineEdit;
    m_inputLine->setPlaceholderText("Message llama3 ...");
    m_inputLine->setFixedHeight(40);

    auto rightButton = m_inputLine->rightButton();
    rightButton->setIcon(QIcon(":/icons/send.svg"));

    auto leftButton = m_inputLine->leftButton();
    leftButton->setIcon(QIcon(":/icons/more-horiz.svg"));

    m_menu = new QMenu(this);
    leftButton->setMenu(m_menu);

    m_contentLayout->addWidget(m_inputLine, 3, 0, 1, 4);
}

void IWelcomePage::setupConnections() {
    auto sendInputText = [this]() {
        if (!m_inputLine->text().isEmpty()) {
            emit SignalHub::instance().on_message_sent(m_inputLine->text(), true);
            m_inputLine->clear();
        }
    };

    connect(m_inputLine->rightButton(), &QPushButton::clicked, this,
            sendInputText);
    connect(m_inputLine, &ILineEdit::returnPressed, this, sendInputText);
    connect(&SignalHub::instance(), &SignalHub::listReceived, this,
            &IWelcomePage::updateMenu);

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

    connect(m_expandButton, &QPushButton::clicked, &SignalHub::instance(),
            &SignalHub::onExpandButtonClicked);
    connect(m_newChatButton, &QPushButton::clicked, &SignalHub::instance(),
            &SignalHub::onNewChatButtonClicked);
    connect(m_userButton, &QPushButton::clicked, &SignalHub::instance(),
            &SignalHub::onUserButtonClicked);
}

void IWelcomePage::updateMenu(const QList<QString> &list) {
    m_menu->clear();
    for (const QString &item : list) {
        QAction *action = new QAction(item, this);
        m_menu->addAction(action);
        connect(action, &QAction::triggered, this, [this, action]() {
            m_inputLine->setPlaceholderText("Message " + action->text() + " ...");
        });
    }
}

void IWelcomePage::retranslateUi() {
    this->setWindowTitle(
        QCoreApplication::translate("IWelcomePage", "Welcome", nullptr));
    m_welcomeLogo->setText(QString());
}
