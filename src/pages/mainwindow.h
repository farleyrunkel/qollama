#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "network/chatbot.h"
#include <QListWidgetItem>

#include "iwelcomepage.h"

#include "ichatwidget.h"
#include "itestwidget.h"
#include "imarketpage.h"

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

    IChatWidget *currentChatList();
protected:
    void showEvent(QShowEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
public slots:
    void appendWordToActiveChat(QString reply);
private slots:

    void addNewChat();
    void on_inputLine_returnPressed();

    void on_comboBox_activated(int index);

    void on_inputLine_textChanged(const QString &arg1);



    void on_expandSideBtn_clicked();

private:
    Ui::MainWindow *ui;
    //std::vector<Document*> m_docus;
    int curr;
    IChatBot* chatbot;

    QPointF clickPosition;
    QWidget* rightTitleBar;
    ITestWidget* test;
    IMarketPage* market;
    void on_chatbot_finish();
    void promoteToMacButtons();
    void setShadeBackground();
};
#endif // MAINWINDOW_H
