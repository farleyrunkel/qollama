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
#include "itestwidget.h"
#include "imarketpage.h"
#include "ihistorylist.h"
#include "iwelcomepage.h"
#include "ichatspage.h"
#include "ileftwindow.h"
#include "irightwindow.h"
#include "isettingpage.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setLeftWindowVisible();
    void addMessage(QString text);

protected:
    void showEvent(QShowEvent *event) override;

public slots:
    void appendWordToActiveChat(QString reply);

private slots:
    void on_inputLine_returnPressed();
    void on_comboBox_activated(int index);
    void on_inputLine_textChanged(const QString &arg1);

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

    QStackedWidget *pages;

    IMarketPage* market;
    IWelcomePage* welcome;
    IChatsPage* chats;
    ISettingPage* settings;

    ILeftWindow *left;
    IRightWindow* right;

    QWidget *centralwidget;
    QSplitter *splitter;

    QStatusBar *statusBar;
    void setupConnections();
};

#endif // MAINWINDOW_H
