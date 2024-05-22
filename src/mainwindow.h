#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "chatbot.h"
#include <QListWidgetItem>

#include "iwelcomepage.h"
#include "iuserpage.h"
#include "ichatwidget.h"
#include "itestwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void on_historyListItem_clicked(QListWidgetItem *item);

    void expandSideWidget();

    void addMessage(QString text);

    IChatWidget *getCurrentChatList();
public slots:
    void appendWordToActiveChat(QString reply);
private slots:

    void addNewChat();
    void on_inputLine_returnPressed();

    void on_comboBox_activated(int index);

    void on_inputLine_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    //std::vector<Document*> m_docus;
    int curr;
    ChatBot* chatbot;

    IWelcomePage* welcome;

    IUserPage* user;

    ITestWidget* test;
};
#endif // MAINWINDOW_H
