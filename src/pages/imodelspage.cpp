#include "imodelspage.h"
#include "galleryphotowidget.h"
#include "configmanager.h"
#include "stylemanager.h"
#include "signalhub.h"

IModelsPage::IModelsPage(QWidget* parent) : QWidget(parent)
{
    setupMainUi(this);
    setupConnections();
}

void IModelsPage::setupMainUi(QWidget * widget)
{
    setObjectName("iChatsPage");
    setContentsMargins(0, 0, 0, 0);
    setStyleSheet("background-color: white;");

    m_mainLayout = new QVBoxLayout(widget);

    m_topArea = new QWidget;
    m_chatsStack = new GalleryWidget;

    m_mainLayout->addWidget(m_topArea);
    m_mainLayout->addWidget(m_chatsStack);

    setupTopArea(m_topArea);
    setupChatArea(m_chatsStack);
}

void IModelsPage::setupTopArea(QWidget *widget) {
    // Set up the top area of the chats page
    auto topAreaLayout = new QHBoxLayout(widget);
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

void IModelsPage::setupChatArea(QWidget* widget)
{
    m_chatsStack->setFrameShape(QFrame::NoFrame);
    m_chatsStack->setContentsMargins(0, 0, 0, 0);
}

void IModelsPage::setupConnections()
{
    connect(m_expandButton, &QPushButton::clicked, &SignalHub::instance(),
            &SignalHub::onExpandButtonClicked);
    connect(m_newChatButton, &QPushButton::clicked, &SignalHub::instance(),
            &SignalHub::onNewChatButtonClicked);
    connect(m_userButton, &QPushButton::clicked, &SignalHub::instance(),
            &SignalHub::onUserButtonClicked);

    connect(&SignalHub::instance(), &SignalHub::onSideAreaHidden, m_expandButton,
            &QPushButton::setVisible);
    connect(&SignalHub::instance(), &SignalHub::onSideAreaHidden, m_newChatButton,
            &QPushButton::setVisible);
}

void IModelsPage::load()
{
    QList<GalleryPhotoData> list;
    srand(time(0));
    int count = rand() % 10 + 5;
    for (int i = 0; i < count; i++)
    {
        QPixmap pixmap(":/images/farley.png");
        QString title = "farley" + QString::number(i);
        QString subTitle = "author：farley" + QString::number(i);
        GalleryPhotoData data{pixmap, title, subTitle};
        list.append(data);
    }

    m_chatsStack->loadData(list);
}

