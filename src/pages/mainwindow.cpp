#include "mainwindow.h"

#include "configmanager.h"
#include "ichatscrollarea.h"
#include "imarketpage.h"
#include "isettingpage.h"
#include "isidearea.h"
#include "iwelcomepage.h"
#include "signalhub.h"
#include "stylemanager.h"
#include <QDialog>
#include <QGraphicsDropShadowEffect>
#include <QJsonObject>
#include <QLabel>
#include <QStandardItemModel>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    setupMainUi(new QSplitter);
    setupStatusBar();
    setupPages();

    setupConnections();
    retranslateUi();
}

MainWindow::~MainWindow() {}

void MainWindow::load() {
    m_models->load();
    m_market->load();
}

void MainWindow::setupMainUi(QSplitter *splitter) {
    setObjectName("MainWindow");
    setWindowModality(Qt::WindowModal);
    setWindowIcon(QIcon(ConfigManager::instance().appIcon()));
    setContextMenuPolicy(Qt::ActionsContextMenu);
    setAutoFillBackground(true);
    setCentralWidget(splitter);

    resize(800, 500);

    StyleManager::instance().loadStyleSheet(":/qss/style.qss");

    // StyleManager::instance().enableBorders(true);

    StyleManager::instance().applyStyleSheet(this);
    StyleManager::instance().applyPalette(this);

    m_left = new ISideArea;
    m_pages = new QStackedWidget;

    m_splitter = splitter;
    m_splitter->setObjectName("splitter");
    m_splitter->setOrientation(Qt::Horizontal);
    m_splitter->setOpaqueResize(false);
    m_splitter->setHandleWidth(0);
    m_splitter->setChildrenCollapsible(false);

    m_splitter->addWidget(m_left);
    m_splitter->addWidget(m_pages);
}

void MainWindow::setupStatusBar() {
    m_statusBar = new QStatusBar(this);
    m_statusBar->setObjectName("statusBar");
    setStatusBar(m_statusBar);
    m_statusBar->setStyleSheet("border-style: hidden;");

    auto statusLabel =
        new QLabel("AI can make mistakes. Check important info.", this);
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setObjectName("statusLabel");
    statusLabel->setAutoFillBackground(true);
    statusLabel->setFrameShape(QFrame::NoFrame);
    m_statusBar->addPermanentWidget(statusLabel, 1);
}

void MainWindow::setupPages() {
    m_chats = new IChatsPage;
    m_welcome = new IWelcomePage;
    m_market = new IMarketPage;
    m_setting = new ISettingPage(this);
    m_models = new IModelsPage;

    m_pages->addWidget(m_chats);
    m_pages->addWidget(m_welcome);
    m_pages->addWidget(m_market);
    m_pages->addWidget(m_models);

    m_pages->setFrameShape(QFrame::NoFrame);
    m_pages->setCurrentWidget(m_welcome);
}

void MainWindow::retranslateUi() {
    setWindowTitle(QCoreApplication::translate("MainWindow", "QOllama", nullptr));
}

void MainWindow::setupConnections() {

    connect(m_left->settingButton(), &QPushButton::clicked, m_setting,
            &ISettingPage::show);
    connect(&SignalHub::instance(), &SignalHub::onNewChatButtonClicked, this,
            [this]() { m_pages->setCurrentWidget(m_welcome); });

    connect(m_left->modelsButton(), &QPushButton::clicked, this,
            [this]() { m_pages->setCurrentWidget(m_models); });

    connect(m_left->promptsButton(), &QPushButton::clicked, this,
            [this]() { m_pages->setCurrentWidget(m_market); });

    connect(m_left->historyList(), &IHistoryList::itemClicked, this,
            [this](QListWidgetItem *item) {
                if (item) {
                    m_pages->setCurrentWidget(m_chats);
                    m_chats->chats()->setCurrentIndex(
                        m_left->historyList()->row(item));
                } else {
                    qDebug() << "Clicked history list item is null.";
                }
            });
    connect(m_left->historyList(), &IHistoryList::itemDeleted, this,
            [&](int row) {
                m_chats->chats()->removeWidget(m_chats->chats()->widget(row));
                m_pages->setCurrentWidget(m_welcome);
            });

    connect(
        &SignalHub::instance(), &SignalHub::newChatAdded, this,
        [this](IChatScrollArea *chat) { m_left->historyList()->addItem(""); });

    connect(&SignalHub::instance(), &SignalHub::onMessageAdded, this,
            [this](const QString &chat) {
                int idx =
                    m_chats->chats()->indexOf(m_chats->chats()->currentWidget());
                m_left->historyList()->item(idx)->setData(Qt::ToolTipRole, chat);
            });
    connect(&SignalHub::instance(), &SignalHub::onExpandButtonClicked, this,
            [this]() { m_left->setVisible(!m_left->isVisible()); });
    connect(&SignalHub::instance(), &SignalHub::onUserButtonClicked, this,
            [this]() { m_setting->show(); });

    connect(&SignalHub::instance(), &SignalHub::on_message_sent, this,
            [&](const QString &) { m_pages->setCurrentWidget(m_chats); });
}
