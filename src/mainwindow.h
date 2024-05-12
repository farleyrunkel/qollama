#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "document.h"
#include "chatbot.h"
#include <QListWidgetItem>
#include "ichatList.h"


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
};
#endif // MAINWINDOW_H
