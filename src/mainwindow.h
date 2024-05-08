#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "document.h"
#include "chatbot.h"

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


private slots:

    void addNewChat();
    void on_inputLine_returnPressed();

private:
    Ui::MainWindow *ui;
    std::vector<Document> m_docus;
    ChatBot chatbot;
};
#endif // MAINWINDOW_H
