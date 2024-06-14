#include "isidearea.h"
#include "configmanager.h"
#include "signalhub.h"
#include "stylemanager.h"
#include <QFile>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QVBoxLayout>

ISideArea::ISideArea(QWidget *parent) : IWidget(parent) {

    setupMainUi(this);

    setupConnections();
}

void ISideArea::setupMainUi(QWidget* widget) {
    setMaximumSize(QSize(170, 16777215));
    setObjectName("leftWindow");

    m_mainLayout = new QVBoxLayout(widget);
    m_mainLayout->setSpacing(2);

    auto topBar = new QWidget;
    auto buttons = new QVBoxLayout;
    m_historyList = new IHistoryList;
    auto bottomLayout = new QVBoxLayout;

    m_mainLayout->addWidget(topBar);
    m_mainLayout->addLayout(buttons);
    m_mainLayout->addWidget(m_historyList);
    m_mainLayout->addLayout(bottomLayout);

    setupTopBar(topBar);
    setupTopButtons(buttons);
    setupHistoryList(m_historyList);
    setupBottomButtons(bottomLayout);
}

void ISideArea::setupTopBar(QWidget *widget) {
    widget->setFixedHeight(ConfigManager::instance()
                               .config("topBar")
                               .toJsonObject()
                               .value("height")
                               .toInt());
    QHBoxLayout *layout = new QHBoxLayout(widget);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    m_expandButton = new QPushButton(QIcon("://icons/sidebar-left.svg"), "");
    m_expandButton->setObjectName("smallButton");

    m_newChatButton = new QPushButton(QIcon(":/icons/create-new.svg"), "");
    m_newChatButton->setObjectName("smallButton");

    layout->addWidget(m_expandButton);
    layout->addStretch(1);
    layout->addWidget(m_newChatButton);
}

void ISideArea::setupTopButtons(QVBoxLayout *layout) {
    QPixmap pix = StyleManager::roundedPixmap(QPixmap("://images/ollama.png"));

    m_modelsButton = new IOverlayButton;
    m_modelsButton->setIcon(QIcon(pix));
    m_modelsButton->setObjectName("bigButton");
    m_modelsButton->setText(tr("Ollama"));
    m_modelsButton->setIconSize(QSize(20, 20));
    m_modelsButton->addSubButton(QIcon(":/icons/create-new.svg"));

    m_messageButton = m_modelsButton->subButton(0);

    m_promptsButton = new QPushButton(QIcon(":/icons/grid.svg"), "");
    m_promptsButton->setObjectName("bigButton");
    m_promptsButton->setText(tr("Explore"));
    m_promptsButton->setIconSize(QSize(20, 20));

    layout->addWidget(m_modelsButton);
    layout->addWidget(m_promptsButton);
}

void ISideArea::setupHistoryList(IHistoryList *widget) {
    widget->setObjectName("historyList");
    widget->setFocusPolicy(Qt::NoFocus);
    widget->setFrameShape(QFrame::NoFrame);
    widget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    widget->setProperty("showDropIndicator", QVariant(false));
    widget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
}

void ISideArea::setupBottomButtons(QVBoxLayout *layout) {
    m_settingButton = new QPushButton(QIcon(":/icons/gear.svg"), "");
    m_settingButton->setObjectName("bigButton");
    m_settingButton->setIconSize(QSize(20, 20));
    m_settingButton->setText(tr("Settings"));

    layout->addWidget(m_settingButton);
}

void ISideArea::setupConnections() {
    connect(this, &ISideArea::hidden, &SignalHub::instance(),
            &SignalHub::onSideAreaHidden);

    connect(m_expandButton, &QPushButton::clicked, &SignalHub::instance(),
            &SignalHub::onExpandButtonClicked);
    connect(m_messageButton, &QPushButton::clicked, &SignalHub::instance(),
            &SignalHub::onNewChatButtonClicked);
    connect(m_newChatButton, &QPushButton::clicked, &SignalHub::instance(),
            &SignalHub::onNewChatButtonClicked);
    connect(m_modelsButton, &QPushButton::clicked, &SignalHub::instance(),
            &SignalHub::onNewChatButtonClicked);
}

ISideArea::~ISideArea() {
}

void ISideArea::load() {}

IHistoryList *ISideArea::historyList() const { return m_historyList; }

QPushButton *ISideArea::expandButton() const { return m_expandButton; }

QPushButton *ISideArea::newChatButton() const { return m_newChatButton; }

IOverlayButton *ISideArea::modelsButton() const { return m_modelsButton; }

QPushButton *ISideArea::promptsButton() const { return m_promptsButton; }

QPushButton *ISideArea::settingButton() const { return m_settingButton; }
