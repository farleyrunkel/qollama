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
    ui->setupUi(this);
    chatbot = new ChatBot();

    this->setWindowIcon(QIcon("://icon/ChatGPT.ico"));

    ui->chatList->setSelectionMode(QAbstractItemView::NoSelection);

    connect(ui->inputButton, &QPushButton::pressed, ui->inputLine, &QLineEdit::returnPressed);
    connect(ui->newChatButton, &QPushButton::pressed, [&](){this->addNewChat();});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addNewChat() {
    auto a = ui->chatList->count();
    if (ui->chatList->count() == 0) {
        return;
    }
    curr_doc = new Document();
    m_docus.emplace_back(curr_doc);
    ui->chatList->clear();
    ui->historyList->addItem("history item");
}

void MainWindow::on_inputLine_returnPressed()
{
    QString text = ui->inputLine->text();

    if (text.trimmed().isEmpty()) {
        return;
    }

    auto userItem = new QListWidgetItem(this->ui->userButton->icon(), this->ui->userButton->text(), ui->chatList);
    userItem->setFlags(userItem->flags() | Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    ui->chatList->addItem(userItem);

    auto messageItem = new QListWidgetItem(ui->chatList);
    auto message = new QLabel(text , ui->chatList);
    message->setMargin(25);
    message->setWordWrap(true);
    message->setAlignment(Qt::AlignTop);
    auto size = message->sizeHint();
    messageItem->setSizeHint(size);
    messageItem->setFlags(messageItem->flags() | Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    ui->chatList->addItem(messageItem);
    ui->chatList->setItemWidget(messageItem, message);
    ui->chatList->update();

    auto reply = chatbot->reply(message->text().toStdString());

    auto userItem1 = new QListWidgetItem(this->ui->newChatButton->icon(), "Chat GPT", ui->chatList);
    userItem1->setFlags(userItem1->flags() | Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    ui->chatList->addItem(userItem1);

    auto messageItem1 = new QListWidgetItem(ui->chatList);
    auto message1 = new QLabel(reply.c_str() , ui->chatList);
    message1->setMargin(25);
    message1->setWordWrap(true);
    message1->setAlignment(Qt::AlignTop);
    auto size1 = message->sizeHint();
    messageItem1->setSizeHint(size1);
    messageItem1->setFlags(messageItem1->flags() | Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    curr_doc->addChat("user", text.toStdString());
    curr_doc->addChat("chagpt", reply);

    ui->chatList->addItem(messageItem1);
    ui->chatList->setItemWidget(messageItem1, message1);
    ui->chatList->update();
    ui->inputLine->clear();
}

