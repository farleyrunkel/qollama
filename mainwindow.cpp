#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QVBoxLayout>
#include "messagebox.h"
#include <QDialog>
#include "ioverlaybutton.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setWindowIcon(QIcon("://icon/ChatGPT.ico"));

    ui->setupUi(this);

    ui->newChatButton->setIcon(QIcon("://icon/logo.png"));

    ui->upgradeButton->setIcon(QIcon("://icon/sparkles.svg"));
    ui->userButton->setIcon(QIcon("://icon/uranus.svg"));

    ui->chatList->setSelectionMode(QAbstractItemView::NoSelection);
    ui->historyList->setObjectName("historyList");

    connect(ui->newChatButton, &INewChatButton::pressed, [&](){ui->historyList->addItem("history item");});
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_inputLine_returnPressed()
{
    QString text = ui->inputLine->text();

    if ("" == text) {return;}

    // 创建一个自定义消息框
    QString user = "John Doe";
    QIcon icon = QIcon(":/icon/uranus.svg"); // 使用资源文件路径创建 QIcon

    auto message = new MessageBox(user, icon, text , ui->chatList);
    auto item = new QListWidgetItem(ui->chatList);

    auto size = message->sizeHint();
    item->setSizeHint(size);
    item->setFlags(item->flags() | Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    ui->chatList->addItem(item);
    ui->chatList->setItemWidget(item, message);

    ui->chatList->update();

    ui->inputLine->clear();
}

