#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QDialog>
#include "ioverlaybutton.h"
#include <QLabel>
#include <QStandardItemModel>
#include "ichatwidget.h"
#include "itestwidget.h"
#include "imarketpage.h"
#include "QJsonObject"
#include <QGraphicsDropShadowEffect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , chatbot (new IChatBot(this))
    , test(new ITestWidget(this))
{
    ui->setupUi(this);

    rightTitleBar = ui->titleBar;

    ui->sendButton->setDisabled(true);
    ui->sendButton->setStatusTip("Nothing");

    setWindowIcon(QIcon("://icon/qollama.png"));
    setShadeBackground();

    auto welcome = new IWelcomePage;
    auto newPage = new QWidget;
    newPage->setLayout(new QHBoxLayout);
    newPage->layout()->addWidget(welcome);
    newPage->setContentsMargins(0, 50, 0, 50);
    ui->stackedWidget->addWidget(newPage);
    ui->stackedWidget->setCurrentWidget(newPage);

    market = new IMarketPage(this);
    auto marketStackWidget = new IWidget;
    marketStackWidget->setLayout(new QHBoxLayout);
    marketStackWidget->layout()->addWidget(market);
    marketStackWidget->setContentsMargins(0, 5, 0, 5);
    ui->stackedWidget->addWidget(marketStackWidget);
    promoteToMacButtons();

    auto userWidget = new QDialog;
    connect(ui->userButton, &QPushButton::clicked, userWidget, &QDialog::show);
    connect(ui->exploreButton, &QPushButton::clicked, market, &IMarketPage::show);
    connect(ui->chatPage, &IWidget::shown, ui->comboBox, &QComboBox::setVisible);
    connect(marketStackWidget, &IWidget::shown, ui->exploreLabel, &QComboBox::setVisible);

    connect(welcome, &IWelcomePage::send, [&](){ui->stackedWidget->setCurrentIndex(0);});
    connect(welcome, &IWelcomePage::send, this, &MainWindow::addMessage);
    connect(ui->newChatButton, &QPushButton::pressed, this, &MainWindow::addNewChat);
    connect(ui->exploreButton, &QPushButton::pressed, [&](){ui->stackedWidget->setCurrentIndex(2);});
    connect(ui->expandButton, &QPushButton::pressed, this, &MainWindow::expandSideWidget);
    connect(ui->newChatBtn, &QPushButton::pressed,  this, &MainWindow::addNewChat);

    connect(chatbot, &IChatBot::replyReceived, this, &MainWindow::appendWordToActiveChat);
    connect(chatbot, &IChatBot::finished, this,  &MainWindow::on_chatbot_finish);

    connect(ui->sendButton, &QPushButton::clicked,[&](){
        if (ui->sendButton->statusTip() == "Pending") {
            chatbot->abort();
            ui->sendButton->statusTip() = "Nothing";
            return ;
        }
        else if (ui->sendButton->statusTip() == "Waiting") {
            on_inputLine_returnPressed();
        }
    });

    connect(ui->inputLine, &QLineEdit::returnPressed, ui->sendButton, &QPushButton::pressed);

    connect(ui->historyList, &IHistoryList::itemClicked, this, &MainWindow::on_historyListItem_clicked);
    connect(ui->historyList, &IHistoryList::itemDeleted, [&](int row){
        ui->stack->removeWidget(ui->stack->widget(row));
        chatbot->abort();
        ui->stackedWidget->setCurrentIndex(1);
    });

    connect(ui->settingButton, &QPushButton::pressed, test, &QWidget::show);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setShadeBackground() {
    setWindowFlags( windowFlags() | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    // 创建中央小部件
    QWidget *centralWidget = this->centralWidget();
    setContentsMargins(4, 4, 4, 4);

    // 创建阴影效果
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(10);
    shadowEffect->setOffset(1, 1);
    shadowEffect->setColor(Qt::gray);

    // 设置阴影效果到中央小部件
    this->setGraphicsEffect(shadowEffect);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        clickPosition = event->globalPosition() - frameGeometry().topLeft();
        event->accept();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPosition().toPoint() - clickPosition.toPoint() );
        event->accept();
    }
}

void MainWindow::on_chatbot_finish() {
    ui->sendButton->setStatusTip("Nothing");
    on_inputLine_textChanged(ui->inputLine->text());
    auto *chatListView = currentChatList();
    if (!chatListView) {
        qDebug() << "Current chat list is null.";
        return;
    }

    IMessageWidget* curr = chatListView->getLatestMessageWidget();
    curr->finish();

}
void MainWindow::expandSideWidget()
{
    ui->left->setVisible(!ui->left->isVisible());
    ui->expandButton->setVisible(!ui->left->isVisible());

    ui->stack->updateGeometry();

    QApplication::processEvents();
}

void MainWindow::appendWordToActiveChat(QString text)
{
    auto chatListView = currentChatList();
    if (!chatListView) {
        qDebug() << "Current chat list is null.";
        return;
    }

    IMessageWidget* curr = chatListView->getLatestMessageWidget();
    curr->appendMessage(text);

    chatListView->scrollToBottom();
}

void MainWindow::addNewChat()
{
    if (ui->stack->count() >= 50) {
        qDebug() << "Maximum chat tabs reached.";
        return;
    }

    IChatWidget *uniqueListWidget = currentChatList();

    if (!uniqueListWidget || uniqueListWidget->isNew()) {
        qDebug() << "Current chat list is null or already contains a new chat.";
        ui->stack->setCurrentWidget(uniqueListWidget);
    }

    ui->stackedWidget->setCurrentIndex(1);
}

IChatWidget *MainWindow::currentChatList()
{
    QWidget *currentTabWidget = ui->stack->currentWidget();
    if (!currentTabWidget) {
        qDebug() << "Current tab widget is null.";
        return nullptr;
    }

    QList<IChatWidget *> listWidgets = currentTabWidget->findChildren<IChatWidget *>();
    if (listWidgets.size() != 1) {
        qDebug() << "Error: There is not exactly one IChatList widget in the current tab.";
        return nullptr;
    }

    return listWidgets.at(0);
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);

    ui->expandButton->hide();
    ui->comboBox->hide();
    ui->exploreLabel->hide();
    test->hide();
}

void MainWindow::addMessage(QString text )
{
    if (chatbot->status() == IChatBot::Status::Receiving
        || chatbot->status() == IChatBot::Status::Requesting
    ) {return;}

    if (text.isEmpty()) {
        qDebug() << "Input text is empty.";
        return;
    }
    ui->stackedWidget->setCurrentIndex(0);
    ui->sendButton->setEnabled(true);
    ui->sendButton->setIcon(QIcon(":/icon/stop.svg"));
    ui->sendButton->setStatusTip("Pending");

    auto chatListView = currentChatList();
    auto hisItem = ui->historyList->currentItem();

    if (!chatListView  || chatListView && !chatListView->isNew()) {
        qDebug() << "Create new chatList.";

        auto tab = new QWidget();
        auto verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        auto newChatList = new IChatWidget(tab);
        verticalLayout->addWidget(newChatList);

        ui->stack->addWidget(tab);
        ui->stack->setCurrentWidget(tab);

        qDebug() << "ui->stack->currentIndex" << ui->stack->currentIndex();
        chatListView = newChatList;

        auto item = new QListWidgetItem(ui->historyList);
        ui->historyList->addItem(item);
        ui->historyList->setCurrentItem(item);

        hisItem = item;
    }

    chatListView->addMessage("farley", QIcon("://icon/farley.jpg").pixmap(30), text);
    chatListView->addMessage(ui->comboBox->currentText(), ui->newChatButton->icon().pixmap(30), "");
    chatListView->scrollToBottom();

    if (hisItem) {
        hisItem->setToolTip(text);
    } else {
        qDebug() << "Current history list item is null.";
    }

    QJsonObject json ;
    json["prompt"] = text;
    json["model"] = ui->comboBox->currentText();

    chatbot->reply(json);
}

void MainWindow::promoteToMacButtons() {
#ifdef Q_OS_WIN // Check if the platform is Windows
    ui->macButtons->close();
#endif

#ifdef Q_OS_MAC // Check if the platform is macOS
    ui->winTitles->close();
#endif
}

void MainWindow::on_historyListItem_clicked(QListWidgetItem *item)
{
    if (item) {
        ui->stackedWidget->setCurrentIndex(0);
        qDebug() << "ui->historyList->row(item)" << ui->historyList->row(item);
        ui->stack->setCurrentIndex(ui->historyList->row(item));
    } else {
        qDebug() << "Clicked history list item is null.";
    }
}

void MainWindow::on_comboBox_activated(int index)
{
    auto text = ui->comboBox->currentText();
    ui->inputLine->setPlaceholderText(QString("Message ") + text + "...");
}

void MainWindow::on_inputLine_textChanged(const QString &arg1)
{
    if ( ui->sendButton->statusTip() == "Pending") {
        return;
    }
    ui->sendButton->setIcon(QIcon(":/icon/arrow-up-circle.svg"));
    if (arg1.isEmpty()) {
        ui->sendButton->setDisabled(true);
        ui->sendButton->setStatusTip("Nothing");
    }
    else {
        ui->sendButton->setEnabled(true);
        ui->sendButton->setStatusTip("Waiting");
    }
}

void MainWindow::on_inputLine_returnPressed()
{
    if (chatbot->status() == IChatBot::Status::Receiving
        || chatbot->status() == IChatBot::Status::Requesting
        ) {return;}

    QString text = ui->inputLine->text().trimmed();

    if (text.isEmpty()) {
        qDebug() << "Input text is empty.";
        return;
    }

    addMessage(text);
    ui->inputLine->clear();
}


void MainWindow::on_expandSideBtn_clicked()
{
    expandSideWidget();
}

