#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QDialog>
#include "ioverlaybutton.h"
#include <QLabel>
#include <QStandardItemModel>
#include "imessagebox.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    chatbot = new ChatBot();
    curr = 0;
    this->setWindowIcon(QIcon("://icon/ChatGPT.ico"));


    ui->historyList->addItem("first item");
    ui->chatList->setSelectionMode(QAbstractItemView::NoSelection);
    // 设置样式表隐藏选项卡标题
    ui->tabWidget->setStyleSheet("QTabBar::tab { width: 0px; }");


    connect(ui->inputButton, &QPushButton::pressed, ui->inputLine, &QLineEdit::returnPressed);
    connect(ui->newChatButton, &QPushButton::pressed, [&](){this->addNewChat();} );
    connect(ui->historyList, &QListWidget::itemClicked, [&](QListWidgetItem *item){
        auto curr = ui->historyList->currentIndex().row();
        ui->tabWidget->setCurrentIndex(curr);
    ;});
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::addNewChat() {

    // auto currChat = ui->tabWidget->currentWidget()->->metaObject()->className();
    // qDebug() << currChat;
    // // if (static_cast<QListWidget*>(currChat)->count() == 0) {
    // //     return;
    // // }


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

    ui->tabWidget->addTab(tab, QString());

    curr = ui->tabWidget->indexOf(tab);
    ui->tabWidget->setCurrentIndex(curr);

    // todo: save chat

    auto curr_doc = new Document();
    m_docus.emplace_back(curr_doc);

    auto item = new QListWidgetItem("history item",ui->historyList );
    ui->historyList->addItem(item);
}


void MainWindow::on_inputLine_returnPressed()
{
    QString text = ui->inputLine->text();

    if (text.trimmed().isEmpty()) {
        return;
    }


    QWidget *currentTabWidget = ui->tabWidget->currentWidget();
    QListWidget * uniqueListWidget = nullptr;
    // 确保当前选项卡非空
    if (currentTabWidget) {
        // 在当前选项卡中查找QListWidget部件
        QList<QListWidget *> listWidgets = currentTabWidget->findChildren<QListWidget *>();

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


    auto userMessage = new IMessagebox(uniqueListWidget);
    userMessage->setIcon(ui->userButton->icon());
    userMessage->setUser( ui->userButton->text());
    userMessage->setChat(text);

    auto userItem = new QListWidgetItem();
    userItem->setFlags(userItem->flags() | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    userItem->setData(Qt::UserRole, ui->userButton->text());
    userItem->setSizeHint(userMessage->sizeHint());
    uniqueListWidget->addItem(userItem);
    uniqueListWidget->setItemWidget(userItem, userMessage);

    ui->inputLine->clear();

    auto reply = chatbot->reply(userMessage->text().toStdString());

    auto message = new IMessagebox(uniqueListWidget);
    message->setIcon(ui->newChatButton->icon());
    message->setUser( this->windowTitle());
    message->setChat(QString::fromStdString(reply));

    auto chatItem = new QListWidgetItem();
    chatItem->setFlags(chatItem->flags() | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    chatItem->setData(Qt::UserRole,this->windowTitle());
    chatItem->setSizeHint(message->sizeHint());
    uniqueListWidget->addItem(chatItem);
    uniqueListWidget->setItemWidget(chatItem, message);
}

