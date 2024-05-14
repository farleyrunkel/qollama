#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "document.h"
#include "chatbot.h"
#include <QListWidgetItem>
#include "ichatList.h"
#include "iwelcomepage.h"


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


    IChatList *getCurrentChatList();
    void onHistoryListItemClicked(QListWidgetItem *item);

    void expandSideWidget();
    void resizeEvent(QResizeEvent *event);
    void on_inputLine_return1Pressed(QString text);
public slots:
    void appendWordToActiveChat(QString reply);
private slots:

    void addNewChat();
    void on_inputLine_returnPressed();

private:
    Ui::MainWindow *ui;
    //std::vector<Document*> m_docus;
    int curr;
    ChatBot* chatbot;

    IWelcomePage* welcome;
};
#endif // MAINWINDOW_H
