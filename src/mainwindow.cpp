#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include "messagebox.h"
#include <QDialog>
#include "ioverlaybutton.h"

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

    if (text.isEmpty()) {
        return;
    }

    QString user = "John Doe";
    QIcon icon = QIcon(":/icon/uranus.svg");

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

