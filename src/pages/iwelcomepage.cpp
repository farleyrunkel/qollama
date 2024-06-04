#include "iwelcomepage.h"

IWelcomePage::IWelcomePage(QWidget *parent)
    :IWidget(parent)
{
    setupLayout();

    setupPushCards();
    setupModelLabel();
    setupLineEdit();

    retranslateUi();

    //setStyleSheet("border: 2px solid red;");


}

void IWelcomePage::setupLayout() {
    setObjectName("IWelcomePage");
    resize(831, 544);
    setContentsMargins(0, 0, 0, 0);

    m_mainLayout = new QGridLayout(this);
    m_mainLayout->setObjectName("mainLayout");
    m_mainLayout->setHorizontalSpacing(20);
    m_mainLayout->setVerticalSpacing(40);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);

    auto m_horizontalSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Preferred);
    m_mainLayout->addItem(m_horizontalSpacer1, 0, 0, 1, 1);

    auto m_horizontalSpacer2 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Preferred);
    m_mainLayout->addItem(m_horizontalSpacer2, 0, 3, 1, 1);
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

     card1 = new IVPushCard;
     card2 = new IVPushCard;
     card3 = new IVPushCard;
     card4 = new IVPushCard;

    card1->setText("Why the sky is blue?");
    card2->setText("Create a personal webpage for me, all in a single file. Ask me 3 questions first on whatever you need to know.");
    card3->setText("Write a short-and-sweet text message inviting my neighbor to a barbecue.");
    card4->setText("Tell me a random fun fact about the Roman Empire");

    card1->setPixmap(QPixmap("://icon/heart-balloon.svg"));
    card2->setPixmap(QPixmap("://icon/art-palette.svg"));
    card3->setPixmap(QPixmap("://icon/electric-light-bulb.svg"));
    card4->setPixmap(QPixmap("://icon/terminal.svg"));

    m_mainLayout->addWidget(card1, 1, 1, 1, 1);
    m_mainLayout->addWidget(card2, 1, 2, 1, 1);
    m_mainLayout->addWidget(card3, 2, 1, 1, 1);
    m_mainLayout->addWidget(card4, 2, 2, 1, 1);
}

void IWelcomePage::setupLineEdit() {
    m_inputLine = new ILineEdit;
    auto rightButton = m_inputLine->rightButton();
    rightButton->setIcon(QIcon(":/icon/send.svg"));

    auto leftButton = m_inputLine->leftButton();
    leftButton->setIcon(QIcon("://icon/more-horiz.svg"));

    //QAction* action = new QAction;
    m_menu = new QMenu;
    leftButton->setMenu(m_menu);
    emit ISignalHub::instance().listRequest();

    m_mainLayout->addWidget(m_inputLine, 3, 0, 1, 4);

    connect(&ISignalHub::instance(), &ISignalHub::listReceived, [this](const QList<QString>& list) {
        for (const auto& a : list) {
            auto action = new QAction(a, this);
            m_menu->addAction(action);
            connect(action, &QAction::triggered, this, [this, action]() {
                this->m_inputLine->setPlaceholderText("Message " + action->text() + " ...");
            });

            emit action->triggered();
        }
    });
}
