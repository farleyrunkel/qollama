#include "mainwindow.h"

#include <QDialog>
#include <QGraphicsDropShadowEffect>
#include <QJsonObject>
#include <QLabel>
#include <QStandardItemModel>
#include <QVBoxLayout>

#include "configmanager.h"
#include "ichatscrollarea.h"
#include "imarketpage.h"
#include "isettingpage.h"
#include "isidearea.h"
#include "itestwidget.h"
#include "iwelcomepage.h"
#include "signalhub.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_ollama(new ollama::Client(this)),
    test(new ITestWidget(this)) {
    setObjectName("MainWindow");
    setWindowModality(Qt::WindowModal);
    setWindowIcon(QIcon(ConfigManager::instance().appIcon()));
    setContextMenuPolicy(Qt::ActionsContextMenu);
    setAutoFillBackground(true);
    resize(800, 500);

    setupSplitter();
    setupStatusBar();
    setupPages();

    setupConnections();
    retranslateUi();
}

MainWindow::~MainWindow() {}

void MainWindow::setupConnections() {
    // connect(chatPage, &IWidget::shown, comboBox, &QComboBox::setVisible);

    connect(m_left->settingButton(), &QPushButton::pressed, m_setting,
            &ISettingPage::show);
    connect(&SignalHub::instance(), &SignalHub::onNewChatButtonClicked, this,
            [this]() { m_pages->setCurrentWidget(m_welcome); });
    connect(m_left->exploreButton(), &QPushButton::pressed, this,
            [this]() { m_pages->setCurrentWidget(m_market); });

    // connect(newChatBtn, &QPushButton::pressed,
    // [&](){pages->setCurrentWidget(welcome);});

    connect(m_ollama, &ollama::Client::replyReceived, this,
            &MainWindow::appendWordToActiveChat);
    connect(m_ollama, &ollama::Client::finished, this,
            &MainWindow::onChatbotFinish);

    // connect(sendButton, &QPushButton::clicked,[&](){
    //     if (sendButton->statusTip() == "Pending") {
    //         chatbot->abort();
    //         sendButton->statusTip() = "Nothing";
    //         return ;
    //     }
    //     else if (sendButton->statusTip() == "Waiting") {
    //         on_inputLine_returnPressed();
    //     }
    // });

    // connect(inputLine, &QLineEdit::returnPressed, sendButton,
    // &QPushButton::pressed);

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

    connect(&SignalHub::instance(), &SignalHub::newChatAdded, this,
            [this](IChatScrollArea *chat) {
                m_left->historyList()->addItem("test");});
    connect(&SignalHub::instance(), &SignalHub::onExpandButtonClicked, this,
            [this]() { m_left->setVisible(!m_left->isVisible()); });
    connect(&SignalHub::instance(), &SignalHub::onUserButtonClicked, this,
            [this]() { m_setting->show();});

    // connect(settingButton, &QPushButton::pressed,
    // [&](){pages->setCurrentWidget(chats);});

    connect(&SignalHub::instance(), &SignalHub::on_message_sent, this,
            [&](const QString &) { m_pages->setCurrentWidget(m_chats); });
}

void MainWindow::onChatbotFinish() {
    // sendButton->setStatusTip("Nothing");
    // on_inputLine_textChanged(inputLine->text());
    auto *chatListView = m_chats->currentChat();
    if (!chatListView) {
        qDebug() << "Current chat list is null.";
        return;
    }

    IMessageBox *curr = chatListView->getLatestMessageWidget();
    curr->finish();
}

void MainWindow::appendWordToActiveChat(QString text) {
    auto chatListView = m_chats->currentChat();
    if (!chatListView) {
        qDebug() << "Current chat list is null.";
        return;
    }

    IMessageBox *curr = chatListView->getLatestMessageWidget();
    curr->appendMessage(text);

    chatListView->scrollToBottom();
}

void MainWindow::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);

    // expandButton->hide();
    // comboBox->hide();
    test->hide();
}

void MainWindow::onComboBoxActivated(int index) {
    // auto text = "";//comboBox->currentText();
    // inputLine->setPlaceholderText(QString("Message ") + text + "...");
}

void MainWindow::onInputLineTextChanged(const QString &arg1) {
    // if ( sendButton->statusTip() == "Pending") {
    //     return;
    // }
    // sendButton->setIcon(QIcon(":/icon/arrow-up-circle.svg"));
    // if (arg1.isEmpty()) {
    //     sendButton->setDisabled(true);
    //     sendButton->setStatusTip("Nothing");
    // }
    // else {
    //     sendButton->setEnabled(true);
    //     sendButton->setStatusTip("Waiting");
    // }
}

void MainWindow::onInputLineReturnPressed() {
    // if (chatbot->status() == ollama::Client::Receiving
    //     || chatbot->status() == ollama::Client::Requesting
    //     ) {return;}

    // QString text = inputLine->text().trimmed();

    // if (text.isEmpty()) {
    //     qDebug() << "Input text is empty.";
    //     return;
    // }

    // addMessage(text);
    // inputLine->clear();
}

void MainWindow::setupSplitter() {
    m_splitter = new QSplitter(this);
    m_splitter->setObjectName("splitter");
    m_splitter->setOrientation(Qt::Horizontal);
    m_splitter->setOpaqueResize(false);
    m_splitter->setHandleWidth(0);
    m_splitter->setChildrenCollapsible(false);

    m_left = new ISideArea;
    m_splitter->addWidget(m_left);

    m_pages = new QStackedWidget;
    m_splitter->addWidget(m_pages);

    setCentralWidget(m_splitter);
}

void MainWindow::setupStatusBar() {
    m_statusBar = new QStatusBar(this);
    m_statusBar->setObjectName("statusBar");
    setStatusBar(m_statusBar);

    auto statusLabel =
        new QLabel("AI can make mistakes. Check important info.", this);
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setObjectName("statusLabel");

    m_statusBar->addPermanentWidget(statusLabel, 1);
}

void MainWindow::setupPages() {
    m_chats = new IChatsPage;
    m_pages->addWidget(m_chats);

    m_welcome = new IWelcomePage;
    m_pages->addWidget(m_welcome);
    m_pages->setCurrentWidget(m_welcome);

    m_market = new IMarketPage(this);
    m_pages->addWidget(m_market);

    m_setting = new ISettingPage(this);
    m_setting->hide();
}

void MainWindow::retranslateUi() {
    setWindowTitle(QCoreApplication::translate("MainWindow", "QOllama", nullptr));
}
