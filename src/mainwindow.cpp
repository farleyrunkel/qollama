#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QDialog>
#include "ioverlaybutton.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon("://icon/ChatGPT.ico"));

    ui->chatList->setSelectionMode(QAbstractItemView::NoSelection);

    connect(ui->newChatButton, &INewChatButton::pressed, [&](){ui->historyList->addItem("history  item");});
    connect(ui->inputButton, &QPushButton::pressed, ui->inputLine, &QLineEdit::returnPressed);
}

MainWindow::~MainWindow()
{
    delete ui;
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
    ui->inputLine->clear();
}

