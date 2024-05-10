#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QDialog>
#include "ioverlaybutton.h"
#include <QLabel>
#include <QStandardItemModel>
#include "imessagebox.h"
#include "chatitemdelegate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    chatbot = new ChatBot();
    curr = 0;

    this->setWindowIcon(QIcon("://icon/ChatGPT.ico"));

    ui->setupUi(this);
    ui->chatList->setSelectionMode(QAbstractItemView::NoSelection);
    ui->historyList->addItem("first item");

    connect(ui->inputButton, &QPushButton::pressed, ui->inputLine, &QLineEdit::returnPressed);
    connect(ui->newChatButton, &QPushButton::pressed, [&](){this->addNewChat();} );
    connect(ui->historyList, &QListWidget::itemClicked, [&](QListWidgetItem *item){
        ui->chatTabs->setCurrentIndex(ui->historyList->currentIndex().row());;});
}

MainWindow::~MainWindow()
{
    delete ui;
    delete chatbot;
}

void MainWindow::addNewChat() {
    IChatList *uniqueListWidget = getCurrentChatList();

    if (uniqueListWidget->isNew()) {
        return;
    }
    auto tab = new QWidget();
    tab->setObjectName("tab");
    auto verticalLayout = new QVBoxLayout(tab);
    verticalLayout->setObjectName("verticalLayout");
    auto chatList = new QListWidget(tab);
    chatList->setObjectName("chatList");
    chatList->setFocusPolicy(Qt::NoFocus);
    chatList->setFrameShape(QFrame::NoFrame);
    chatList->setFrameShadow(QFrame::Plain);

    verticalLayout->addWidget(chatList);

    ui->chatTabs->addTab(tab, QString());

    curr = ui->chatTabs->indexOf(tab);
    ui->chatTabs->setCurrentIndex(curr);

    // todo: save chat

    auto curr_doc = new Document();
    m_docus.emplace_back(curr_doc);

    auto item = new QListWidgetItem("history item",ui->historyList );
    ui->historyList->addItem(item);
}

IChatList* MainWindow::getCurrentChatList()
{
    QWidget *currentTabWidget = ui->chatTabs->currentWidget();
    IChatList * uniqueListWidget = nullptr;
    // 确保当前选项卡非空
    if (currentTabWidget) {
        // 在当前选项卡中查找QListWidget部件
        QList<IChatList *> listWidgets = currentTabWidget->findChildren<IChatList *>();

        // 确保只有一个QListWidget部件
        if (listWidgets.size() == 1) {
            uniqueListWidget = listWidgets.at(0);
            // 在这里使用uniqueListWidget进行需要的操作
        } else {
            qDebug() << "Error: There is not exactly one QListWidget in the current tab.";
        }
    } else {
        qDebug() << "Error: Current tab widget is null.";
    }
    return uniqueListWidget;
}

void MainWindow::on_inputLine_returnPressed()
{
    QString text = ui->inputLine->text();

    if (text.trimmed().isEmpty()) {
        return;
    }

    auto *chatListView = getCurrentChatList();

    // auto userMessage = new IMessagebox(uniqueListWidget);
    // userMessage->setIcon(ui->userButton->icon());
    // userMessage->setUser( ui->userButton->text());
    // userMessage->setChat(text);

    // auto userItem = new QListWidgetItem();
    // userItem->setFlags(userItem->flags() | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    // userItem->setData(Qt::UserRole, ui->userButton->text());
    // userItem->setSizeHint(userMessage->sizeHint());
    // uniqueListWidget->addItem(userItem);
    // uniqueListWidget->setItemWidget(userItem, userMessage);

    // ui->inputLine->clear();

    // auto reply = chatbot->reply(userMessage->text().toStdString());

    // auto message = new IMessagebox(uniqueListWidget);
    // message->setIcon(ui->newChatButton->icon());
    // message->setUser( this->windowTitle());
    // message->setChat(QString::fromStdString(reply));

    // auto chatItem = new QListWidgetItem();
    // chatItem->setFlags(chatItem->flags() | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    // chatItem->setData(Qt::UserRole,this->windowTitle());
    // chatItem->setSizeHint(message->sizeHint());
    // uniqueListWidget->addItem(chatItem);
    // uniqueListWidget->setItemWidget(chatItem, message);

    QStandardItemModel *model = new QStandardItemModel;
    //QListView *chatListView = new QListView;
    ChatItemDelegate *chatDelegate = new ChatItemDelegate(chatListView);

    // 添加聊天数据到模型中
    QVariantMap chatData1, chatData2;
    chatData1["icon"] = ui->userButton->icon();
    chatData1["username"] = "User1";
    chatData1["message"] = "Hello, how are you?";
    QStandardItem *item1 = new QStandardItem;
    item1->setData(chatData1, Qt::DisplayRole);
    model->appendRow(item1);

    chatData2["icon"] = ui->userButton->icon();
    chatData2["username"] = "User2";
    chatData2["message"] = text;
    QStandardItem *item2 = new QStandardItem;
    item2->setData(chatData2, Qt::DisplayRole);
    model->appendRow(item2);

    // 设置模型和委托类
    chatListView->setModel(model);
    chatListView->setItemDelegate(chatDelegate);
}

