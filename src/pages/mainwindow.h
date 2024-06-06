#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFrame>
#include <QHBoxLayout>
#include <QIcon>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QPushButton>
#include <QSplitter>
#include <QStackedWidget>
#include <QStatusBar>
#include <QVBoxLayout>

#include "client.h"
#include "ichatspage.h"
#include "imarketpage.h"
#include "isettingpage.h"
#include "isidearea.h"
#include "itestwidget.h"
#include "iwelcomepage.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void showEvent(QShowEvent *event) override;

public slots:
    void appendWordToActiveChat(QString reply);

private slots:
    void onInputLineReturnPressed();
    void onComboBoxActivated(int index);
    void onInputLineTextChanged(const QString &arg1);
    void onChatbotFinish();

private:
    void setupPages();
    void setupStatusBar();
    void setupSplitter();
    void setupConnections();
    void retranslateUi();

    ollama::Client *m_ollama;

    ITestWidget *test;

    QStackedWidget *m_pages;

    IMarketPage *m_market;
    IWelcomePage *m_welcome;
    IChatsPage *m_chats;
    ISettingPage *m_setting;

    ISideArea *m_left;

    QWidget *m_centralwidget;
    QSplitter *m_splitter;

    QStatusBar *m_statusBar;
};

#endif // MAINWINDOW_H
