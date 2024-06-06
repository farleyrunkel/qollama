#include <QMenu>
#include <QSpacerItem>
#include <QMouseEvent>
#include "iwelcomepage.h"
#include "signalhub.h"
#include <QStackedLayout>
#include <QLCDNumber>
#include <QScopedPointer>

IWelcomePage::IWelcomePage(QWidget *parent)
    : IWidget(parent)
{
    setupMainLayout();
    setupTopArea();
    setupContentArea();
    setupConnections();
    retranslateUi();
}

void IWelcomePage::setupMainLayout()
{
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
}

void IWelcomePage::setupTopArea()
{
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

void IWelcomePage::setupContentArea()
{
    setupContentCards();
    setupContentLabel();
    setupContentLineEdit();
}

void IWelcomePage::setupContentCards()
{
    m_card1 = createPushCard("Why the sky is blue?", "://icon/heart-balloon.svg");
    m_card2 = createPushCard("Create a personal webpage for me, all in a single file. Ask me 3 questions first on whatever you need to know.", "://icon/art-palette.svg");
    m_card3 = createPushCard("Write a short-and-sweet text message inviting my neighbor to a barbecue.", "://icon/electric-light-bulb.svg");
    m_card4 = createPushCard("Tell me a random fun fact about the Roman Empire", "://icon/terminal.svg");

    m_contentLayout->addWidget(m_card1, 1, 1, 1, 1);
    m_contentLayout->addWidget(m_card2, 1, 2, 1, 1);
    m_contentLayout->addWidget(m_card3, 2, 1, 1, 1);
    m_contentLayout->addWidget(m_card4, 2, 2, 1, 1);
}

IVPushCard* IWelcomePage::createPushCard(const QString& text, const QString& iconPath)
{
    auto card = new IVPushCard;
    card->setText(text);
    card->setPixmap(QPixmap(iconPath));
    return card;
}

void IWelcomePage::setupContentLabel()
{
    m_welcomeLogo = new QLabel;
    m_welcomeLogo->setObjectName("welcomeLogo");
    m_welcomeLogo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_welcomeLogo->setMinimumSize(QSize(200, 70));
    m_welcomeLogo->setMaximumSize(QSize(4000, 100));
    m_welcomeLogo->setStyleSheet("image: url(://images/qollama-logo-name.png);");
    m_welcomeLogo->setAlignment(Qt::AlignCenter);

    m_contentLayout->addWidget(m_welcomeLogo, 0, 1, 1, 2);
}

void IWelcomePage::setupContentLineEdit()
{
    m_inputLine = new ILineEdit;
    m_inputLine->setPlaceholderText("Message llama3 ...");
    m_inputLine->setFixedHeight(40);

    auto rightButton = m_inputLine->rightButton();
    rightButton->setIcon(QIcon(":/icon/send.svg"));

    auto leftButton = m_inputLine->leftButton();
    leftButton->setIcon(QIcon(":/icon/more-horiz.svg"));

    m_menu = new QMenu(this);
    leftButton->setMenu(m_menu);

    m_contentLayout->addWidget(m_inputLine, 3, 0, 1, 4);
}

void IWelcomePage::setupConnections()
{
    auto sendInputText = [this]() {
        if (!m_inputLine->text().isEmpty()) {
            emit SignalHub::instance().on_message_sent(m_inputLine->text(), true);
            m_inputLine->clear();
        }
    };

    connect(m_inputLine->rightButton(), &QPushButton::clicked, this, sendInputText);
    connect(m_inputLine, &ILineEdit::returnPressed, this, sendInputText);
    connect(&SignalHub::instance(), &SignalHub::listReceived, this, &IWelcomePage::updateMenu);

    connect(m_expandButton, &QPushButton::clicked, &SignalHub::instance(), &SignalHub::onExpandButtonClicked);
    connect(&SignalHub::instance(), &SignalHub::onSideAreaHidden, m_expandButton, &QPushButton::setVisible);
    connect(&SignalHub::instance(), &SignalHub::onSideAreaHidden, m_newChatButton, &QPushButton::setVisible);
    connect(&SignalHub::instance(), &SignalHub::onSideAreaHidden, m_userButton, &QPushButton::setVisible);
}

void IWelcomePage::updateMenu(const QList<QString>& list)
{
    m_menu->clear();
    for (const QString& item : list) {
        QAction* action = new QAction(item, this);
        m_menu->addAction(action);
        connect(action, &QAction::triggered, this, [this, action]() {
            m_inputLine->setPlaceholderText("Message " + action->text() + " ...");
        });
    }
}

QPushButton* IWelcomePage::createButton(const QString& iconPath)
{
    auto button = new QPushButton;
    button->setIcon(QIcon(iconPath));
    button->setFixedSize(QSize(30, 30));
    button->setObjectName("smallButton");
    return button;
}

void IWelcomePage::retranslateUi()
{
    this->setWindowTitle(QCoreApplication::translate("IWelcomePage", "Welcome", nullptr));
    m_welcomeLogo->setText(QString());
}
