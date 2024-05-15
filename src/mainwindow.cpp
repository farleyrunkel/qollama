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
    welcome = new IWelcomePage(ui->chatTabs);
    chatbot = new ChatBot();
    curr = 0;

    this->setWindowIcon(QIcon("://icon/qollama.png"));

    ui->chatList->setSelectionMode(QAbstractItemView::NoSelection);
    ui->historyList->addItem("");
    ui->chatTabs->tabBar()->hide();

    connect(ui->inputButton, &QPushButton::pressed, ui->inputLine, &QLineEdit::returnPressed);
    connect(ui->newChatButton, &QPushButton::pressed, this, &MainWindow::addNewChat);
//    connect(ui->newChatButton, &QPushButton::pressed, welcome, &IWelcomePage::show);
    connect(ui->historyList, &QListWidget::itemClicked, this, &MainWindow::onHistoryListItemClicked);
    connect(chatbot, &ChatBot::replyReceived, this, &MainWindow::appendWordToActiveChat);
    connect(ui->expandButton, &QPushButton::pressed, this, &MainWindow::expandSideWidget);
    connect(welcome, &IWelcomePage::send, this, &MainWindow::addMessage);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete chatbot;
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    if (welcome) {

          welcome->setGeometry(ui->chatTabs->currentWidget()->geometry());
    }
}


void MainWindow::expandSideWidget() {
    if ( ui->frameleft->isHidden() ) {
        ui->frameleft->show();
        ui->expandButton->setIcon(QIcon(":/icon/full-screen.svg"));
    }
    else {
        ui->frameleft->hide();
        ui->expandButton->setIcon(QIcon(":/icon/full-screen-zoom.svg"));
    }
    ui->chatTabs->updateGeometry();

    QApplication::processEvents();

    welcome->setGeometry(ui->chatTabs->currentWidget()->geometry());
}

void MainWindow::appendWordToActiveChat(QString text) {

    auto *chatListView = getCurrentChatList();
    if (!chatListView) {
        qDebug() << "Current chat list is null.";
        return;
    }

    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(chatListView->model());
    if (!model) {
        qDebug() << "Chat list model is null.";
        return;
    }

    QModelIndex lastIndex = model->index(model->rowCount() - 1, 0);
    QStandardItem* lastItem = model->itemFromIndex(lastIndex);
    if (!lastItem) {
        lastItem = new QStandardItem();
        model->appendRow(lastItem);
    }

    // Update message field of the last item
    QVariant itemData = lastItem->data(Qt::DisplayRole);
    QVariantMap chatData = itemData.toMap();
    chatData["message"] = chatData["message"].toString() + text;
    lastItem->setData(chatData, Qt::DisplayRole);

    qDebug() << "appendText:" << text;

    // Emit dataChanged signal to refresh the view
    emit model->dataChanged(lastIndex, lastIndex);
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
    verticalLayout->setSpacing(0);
    verticalLayout->setObjectName("verticalLayout");
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    auto chatList = new IChatList(tab);
    chatList->setFocusPolicy(Qt::NoFocus);
    chatList->setFrameShape(QFrame::NoFrame);
    chatList->setFrameShadow(QFrame::Plain);
    chatList->setSelectionMode(QAbstractItemView::NoSelection);

    verticalLayout->addWidget(chatList);

    ui->chatTabs->addTab(tab, QString());

    curr = ui->chatTabs->indexOf(tab);
    ui->chatTabs->setCurrentIndex(curr);

    // todo: save chat

    auto item = new QListWidgetItem("",ui->historyList );
    ui->historyList->addItem(item);


    welcome->show();

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

    addMessage(text);
    ui->inputLine->clear();
}


void MainWindow::addMessage(QString text )
{

    welcome->hide();


    if (text.isEmpty()) {
        qDebug() << "Input text is empty.";
        return;
    }
    auto *chatListView = getCurrentChatList();
    if (!chatListView) {
        qDebug() << "Current chat list is null.";
        return;
    }

    chatListView->addItem(ui->userButton->icon(),  ui->userButton->text(), text);
    chatListView->addItem(ui->newChatButton->icon(), this->windowTitle(), "");

    QMap<QString, QString> map;
    map["message"] = text;
    map["model"] = ui->comboBox->currentText();

    auto hisItem = ui->historyList->item(ui->chatTabs->currentIndex());
    if (hisItem) {
        hisItem->setToolTip(text);
    } else {
        qDebug() << "Current history list item is null.";
    }

    chatbot->reply(map);
}

void MainWindow::onHistoryListItemClicked(QListWidgetItem *item)
{
    if (item) {
        ui->chatTabs->setCurrentIndex(ui->historyList->row(item));
    } else {
        qDebug() << "Clicked history list item is null.";
    }
}

void MainWindow::on_comboBox_activated(int index)
{
    auto text = ui->comboBox->currentText();
    ui->inputLine->setPlaceholderText(QString("Message ") + text + "...");
}

