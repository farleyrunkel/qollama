#ifndef ICHATSPAGE_H
#define ICHATSPAGE_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include "iwidget.h"
#include <QStackedWidget>
#include "ilineedit.h"
#include "ichatwidget.h"
#include "isignalhub.h"
#include <QJsonObject>

class IChatsPage : public QWidget
{
    Q_OBJECT

public:
    explicit IChatsPage(QWidget *parent = nullptr);;

    void addQuestion(const QString& text);

   IChatWidget* addChat();

   IChatWidget* currentChat();

signals:

private:
    void setupUI();


private:
    QVBoxLayout* mainLayout;
    QStackedWidget* chatsContainer;
    ILineEdit* lineEdit;
};

#endif // ICHATSPAGE_H
