#include "isidearea.h"
#include "signalhub.h"
#include "stylemanager.h"
#include <QFile>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QVBoxLayout>

ISideArea::ISideArea(QWidget *parent) : IWidget(parent) {

    setupMainLayout(new QVBoxLayout);

    setupTitleBar(layout(0));
    setupTopButtons(layout(1));
    setupHistoryList(layout(2));
    setupBottomButtons(layout(3));

    setupConnections();
}

void ISideArea::setupMainLayout(QVBoxLayout *layout) {
    setMaximumSize(QSize(170, 16777215));
    setObjectName("leftWindow");
    setLayout(layout);

    m_mainLayout = layout;
    m_mainLayout->setSpacing(2);

    m_layouts.append(new QHBoxLayout);
    m_layouts.append(new QVBoxLayout);
    m_layouts.append(new QVBoxLayout);
    m_layouts.append(new QVBoxLayout);

    for (const auto a : m_layouts) {
        m_mainLayout->addLayout(a);
    }
}

void ISideArea::setupTitleBar(QLayout *layout) {
    QHBoxLayout *hLayout = qobject_cast<QHBoxLayout *>(layout);
    hLayout->setSpacing(0);
    hLayout->setContentsMargins(0, 0, 0, 0);

    m_expandButton = new QPushButton(QIcon("://icons/sidebar-left.svg"), "");
    m_expandButton->setObjectName("smallButton");

    m_newChatButton = new QPushButton(QIcon(":/icons/create-new.svg"), "");
    m_newChatButton->setObjectName("smallButton");

    hLayout->addWidget(m_expandButton);
    hLayout->addStretch(1);
    hLayout->addWidget(m_newChatButton);
}

void ISideArea::setupTopButtons(QLayout *layout) {

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

void ISideArea::setupHistoryList(QLayout *layout) {
    m_historyList = new IHistoryList(this);
    m_historyList->setObjectName("historyList");
    m_historyList->setFocusPolicy(Qt::NoFocus);
    m_historyList->setFrameShape(QFrame::NoFrame);
    m_historyList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_historyList->setProperty("showDropIndicator", QVariant(false));
    m_historyList->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

    layout->addWidget(m_historyList);
}

void ISideArea::setupBottomButtons(QLayout *layout) {

    m_settingButton = new QPushButton(QIcon(":/icons/gear.svg"), "");
    m_settingButton->setObjectName("bigButton");
    m_settingButton->setIconSize(QSize(20, 20));
    m_settingButton->setText(tr("Settings"));

    layout->addWidget(m_settingButton);
}

QLayout *ISideArea::layout(int i) const {
    if (i < 0 || i >= m_layouts.size()) {
        throw std::out_of_range("Index out of range in ISideArea::layouts");
    }
    return m_layouts[i];
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
    for (auto layout : m_layouts) {
        delete layout;
    }
    m_layouts.clear();
}

IHistoryList *ISideArea::historyList() const { return m_historyList; }

QPushButton *ISideArea::expandButton() const { return m_expandButton; }

QPushButton *ISideArea::newChatButton() const { return m_newChatButton; }

IOverlayButton *ISideArea::modelsButton() const { return m_modelsButton; }

QPushButton *ISideArea::promptsButton() const { return m_promptsButton; }

QPushButton *ISideArea::settingButton() const { return m_settingButton; }
