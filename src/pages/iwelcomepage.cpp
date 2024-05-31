#include "iwelcomepage.h"

IWelcomePage::IWelcomePage(QWidget *parent) {
    setupUi(this);
    //setStyleSheet("border: 2px solid red;");
}

void IWelcomePage::mousePressEvent(QMouseEvent *event) {
    QWidget::mousePressEvent(event);
    // Your custom mouse press event handling here
}

void IWelcomePage::setupUi(QWidget *parent) {
    parent->setObjectName("IWelcomePage");
    parent->resize(831, 544);
    parent->setAutoFillBackground(false);
    parent->setContentsMargins(0, 0, 0, 0);

    m_mainLayout = new QGridLayout(parent);
    m_mainLayout->setObjectName("mainLayout");
    m_mainLayout->setHorizontalSpacing(11);
    m_mainLayout->setVerticalSpacing(22);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_welcomeLogo = new QLabel(parent);
    m_welcomeLogo->setObjectName("welcomeLogo");
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_welcomeLogo->setSizePolicy(sizePolicy);
    m_welcomeLogo->setMinimumSize(QSize(200, 70));
    m_welcomeLogo->setMaximumSize(QSize(4000, 100));
    m_welcomeLogo->setStyleSheet("image: url(:/images/qollama-text.png);");
    m_welcomeLogo->setAlignment(Qt::AlignCenter);
    m_welcomeLogo->setFrameShape(QFrame::Shape::NoFrame);
    m_mainLayout->addWidget(m_welcomeLogo, 0, 1, 1, 2);

    addPushCardWidgets();

    m_inputLine = new ILineEdit(parent);
    auto m_inputButton = m_inputLine->rightButton();
    m_inputButton->setObjectName("inputButton");
    QIcon icon;
    icon.addFile(":/icon/send.svg", QSize(), QIcon::Normal, QIcon::Off);
    m_inputButton->setIcon(icon);
    m_mainLayout->addWidget(m_inputLine, 3, 1, 1, 2);

    auto m_horizontalSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Preferred);
    m_mainLayout->addItem(m_horizontalSpacer1, 3, 0, 1, 1);

    auto m_horizontalSpacer2 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Preferred);
    m_mainLayout->addItem(m_horizontalSpacer2, 3, 3, 1, 1);

    retranslateUi();
}

void IWelcomePage::retranslateUi() {
    this->setWindowTitle(QCoreApplication::translate("IWelcomePage", "Welcome", nullptr));
    m_welcomeLogo->setText(QString());
}

void IWelcomePage::addPushCardWidgets() {

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
