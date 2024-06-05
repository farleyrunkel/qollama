#include <Qmenu>
#include <QSpacerItem>
#include <QMouseEvent>
#include "iwelcomepage.h"
#include "signalhub.h"
#include <QStackedLayout>
#include <QLCDNumber>

IWelcomePage::IWelcomePage(QWidget *parent)
    : IWidget(parent)
{
    setupLayout();
    setupPushCards();
    setupModelLabel();
    setupLineEdit();

    setupConnections();

    retranslateUi();
}

void IWelcomePage::setupConnections() {

    auto sendInputText = [this]() {
        if (!m_inputLine->text().isEmpty()) {
            emit SignalHub::instance().on_message_sent(m_inputLine->text(), true);
            m_inputLine->clear();
        }
    };

    connect(m_inputLine->rightButton(), &QPushButton::clicked, this, sendInputText);
    connect(m_inputLine, &ILineEdit::returnPressed, this, sendInputText);
    connect(&SignalHub::instance(), &SignalHub::listReceived, this, &IWelcomePage::updateMenu);
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

void IWelcomePage::setupLayout() {
    setObjectName("IWelcomePage");
    setContentsMargins(0, 0, 0, 0);

    auto new_mainLayot = new QVBoxLayout(this);
    auto new_topLayout = new QHBoxLayout(this);

    // 初始化按钮并添加到左侧和右侧
    m_expandButton = new QPushButton;
    m_expandButton->setIcon(QIcon("://icon/sidebar-left.svg"));
    m_expandButton->setFixedSize(QSize(30, 30));
    m_expandButton->setObjectName("smallButton");

    m_userButton = new QPushButton;
    m_userButton->setIcon(QIcon("://icon.png"));
    m_userButton->setFixedSize(QSize(30, 30));
    m_userButton->setObjectName("smallButton");

    new_topLayout->addWidget(m_expandButton);
    new_topLayout->addStretch(1);
    new_topLayout->addWidget(m_userButton);
    m_expandButton->hide();
    m_mainLayout = new QGridLayout(this);
    m_mainLayout->setObjectName("mainLayout");
    m_mainLayout->setHorizontalSpacing(20);
    m_mainLayout->setVerticalSpacing(40);
    m_mainLayout->setContentsMargins(40, 0, 40, 0);

    new_mainLayot->addLayout(new_topLayout);
    new_mainLayot->addLayout(m_mainLayout);
}

QPushButton* IWelcomePage::expandButton() const {
    return m_expandButton;
}

void IWelcomePage::retranslateUi() {
    this->setWindowTitle(QCoreApplication::translate("IWelcomePage", "Welcome", nullptr));
    m_welcomeLogo->setText(QString());
}

void IWelcomePage::setupModelLabel() {
    m_welcomeLogo = new QLabel;
    m_welcomeLogo->setObjectName("welcomeLogo");
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_welcomeLogo->setSizePolicy(sizePolicy);
    m_welcomeLogo->setMinimumSize(QSize(200, 70));
    m_welcomeLogo->setMaximumSize(QSize(4000, 100));
    m_welcomeLogo->setStyleSheet("image: url(://images/qollama-logo-name.png);");
    m_welcomeLogo->setAlignment(Qt::AlignCenter);
    m_welcomeLogo->setFrameShape(QFrame::Shape::NoFrame);
    m_mainLayout->addWidget(m_welcomeLogo, 0, 1, 1, 2);
}

void IWelcomePage::setupPushCards() {
    m_card1 = new IVPushCard;
    m_card2 = new IVPushCard;
    m_card3 = new IVPushCard;
    m_card4 = new IVPushCard;

    m_card1->setText("Why the sky is blue?");
    m_card2->setText("Create a personal webpage for me, all in a single file. Ask me 3 questions first on whatever you need to know.");
    m_card3->setText("Write a short-and-sweet text message inviting my neighbor to a barbecue.");
    m_card4->setText("Tell me a random fun fact about the Roman Empire");

    m_card1->setPixmap(QPixmap("://icon/heart-balloon.svg"));
    m_card2->setPixmap(QPixmap("://icon/art-palette.svg"));
    m_card3->setPixmap(QPixmap("://icon/electric-light-bulb.svg"));
    m_card4->setPixmap(QPixmap("://icon/terminal.svg"));

    m_mainLayout->addWidget(m_card1, 1, 1, 1, 1);
    m_mainLayout->addWidget(m_card2, 1, 2, 1, 1);
    m_mainLayout->addWidget(m_card3, 2, 1, 1, 1);
    m_mainLayout->addWidget(m_card4, 2, 2, 1, 1);
}

void IWelcomePage::setupLineEdit() {
    m_inputLine = new ILineEdit;
    m_inputLine->setPlaceholderText("Message llama3 ...");

    auto rightButton = m_inputLine->rightButton();
    rightButton->setIcon(QIcon(":/icon/send.svg"));

    auto leftButton = m_inputLine->leftButton();
    leftButton->setIcon(QIcon("://icon/more-horiz.svg"));

    m_menu = new QMenu;
    leftButton->setMenu(m_menu);

    m_mainLayout->addWidget(m_inputLine, 3, 0, 1, 4);
}
