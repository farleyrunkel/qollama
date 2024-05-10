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
    ui->historyList->addItem("");

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
    auto chatList = new IChatList(tab);
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

    auto item = new QListWidgetItem("",ui->historyList );
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

    auto reply = chatbot->reply(text.toStdString());

    auto *chatListView = getCurrentChatList();

    auto model =  static_cast<QStandardItemModel*>(chatListView->model());
    // 添加聊天数据到模型中
    QVariantMap chatData1, chatData2;
    chatData1["icon"] = ui->userButton->icon();
    chatData1["username"] = ui->userButton->text();
    chatData1["message"] = text;
    QStandardItem *item1 = new QStandardItem;
    item1->setData(chatData1, Qt::DisplayRole);
    model->appendRow(item1);

    chatData2["icon"] = ui->newChatButton->icon();
    chatData2["username"] = this->windowTitle();
    chatData2["message"] = QString::fromStdString(reply);
    QStandardItem *item2 = new QStandardItem;
    item2->setData(chatData2, Qt::DisplayRole);
    model->appendRow(item2);

    auto hisItem = ui->historyList->item(ui->chatTabs->currentIndex());
    hisItem->setText( QString::fromStdString(reply));

    ui->inputLine->clear();
}

