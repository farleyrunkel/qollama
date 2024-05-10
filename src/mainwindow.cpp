#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QDialog>
#include "ioverlaybutton.h"
#include <QLabel>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    chatbot = new ChatBot();
    curr = 0;

    this->setWindowIcon(QIcon("://icon/ollama.png"));

    ui->setupUi(this);
    ui->chatList->setSelectionMode(QAbstractItemView::NoSelection);
    ui->historyList->addItem("");

    connect(ui->inputButton, &QPushButton::pressed, ui->inputLine, &QLineEdit::returnPressed);
    connect(ui->newChatButton, &QPushButton::pressed, this, &MainWindow::addNewChat);
    connect(ui->historyList, &QListWidget::itemClicked, this, &MainWindow::onHistoryListItemClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete chatbot;
}

void MainWindow::addNewChat() {
    if (ui->chatTabs->count() >= 50) {
        qDebug() << "Maximum chat tabs reached.";
        return;
    }

    IChatList *uniqueListWidget = getCurrentChatList();

    if (!uniqueListWidget || uniqueListWidget->isNew()) {
        qDebug() << "Current chat list is null or already contains a new chat.";
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
    if (!currentTabWidget) {
        qDebug() << "Current tab widget is null.";
        return nullptr;
    }

    QList<IChatList *> listWidgets = currentTabWidget->findChildren<IChatList *>();
    if (listWidgets.size() != 1) {
        qDebug() << "Error: There is not exactly one IChatList widget in the current tab.";
        return nullptr;
    }

    return listWidgets.at(0);
}

void MainWindow::on_inputLine_returnPressed()
{
    QString text = ui->inputLine->text().trimmed();

    if (text.isEmpty()) {
        qDebug() << "Input text is empty.";
        return;
    }

    auto reply = chatbot->reply(text.toStdString());

    auto *chatListView = getCurrentChatList();

    if (!chatListView) {
        qDebug() << "Current chat list is null.";
        return;
    }

    auto model = static_cast<QStandardItemModel*>(chatListView->model());
    if (!model) {
        qDebug() << "Chat list model is null.";
        return;
    }

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
    if (hisItem) {
        hisItem->setText(QString::fromStdString(reply));
    } else {
        qDebug() << "Current history list item is null.";
    }

    ui->inputLine->clear();
}

void MainWindow::onHistoryListItemClicked(QListWidgetItem *item)
{
    if (item) {
        ui->chatTabs->setCurrentIndex(ui->historyList->row(item));
    } else {
        qDebug() << "Clicked history list item is null.";
    }
}
