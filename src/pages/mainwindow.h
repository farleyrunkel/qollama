#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSplitter>
#include <QStackedWidget>
#include <QStatusBar>
#include <QIcon>

#include "client.h"
#include "ichatwidget.h"
#include "itestwidget.h"
#include "imarketpage.h"
#include "ihistorylist.h"
#include "ioverlaybutton.h"
#include "iwelcomepage.h"
#include "ichatspage.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void on_historyListItem_clicked(QListWidgetItem *item);
    void expandSideWidget();
    void addMessage(QString text);

protected:
    void showEvent(QShowEvent *event) override;

public slots:
    void appendWordToActiveChat(QString reply);

private slots:
    void on_inputLine_returnPressed();
    void on_comboBox_activated(int index);
    void on_inputLine_textChanged(const QString &arg1);
    void on_expandSideBtn_clicked();

private:
    void setupUi();
    void retranslateUi();
    void on_chatbot_finish();
    void promoteToMacButtons();
    void setShadeBackground();

    // Only key member variables
    ollama::Client* chatbot;

    IHistoryList* historyList;

    ITestWidget* test;

    IMarketPage* market;
    IWelcomePage* welcome;
    IChatsPage* chats;

    QWidget *centralwidget;
    QSplitter *splitter;
    QFrame *left;
    QStackedWidget *pages;
    QStatusBar *statusBar;
    QPushButton *expandSideBtn;
    QPushButton *newChatBtn;
    INewChatButton *newChatButton;
    QPushButton *exploreButton;
    QPushButton *settingButton;
};

#endif // MAINWINDOW_H
