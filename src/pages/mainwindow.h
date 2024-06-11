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
#include "iwelcomepage.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:

private:
    void setupPages();
    void setupStatusBar();
    void setupMainUi();
    void setupConnections();
    void retranslateUi();

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
