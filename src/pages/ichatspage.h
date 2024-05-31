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

    INJECT_SHOW_HIDE_EVENTS(IChatsPage)

public:
    explicit IChatsPage(QWidget *parent = nullptr): QWidget(parent)


    {

        setupUI();

        connect(&ISignalHub::instance(), &ISignalHub::on_IVPushCard_clicked, this, &IChatsPage::addQuestion);
    };

    void addQuestion(const QString& text) {

        if (text.isEmpty()) {return;}

        if (currentChat() == nullptr) {
            addChat();
        }

        currentChat()->addMessage(text, "user");
        currentChat()->addMessage("", "llama3");

        QJsonObject json ;
        json["prompt"] = text;
        json["model"] = "llama3";

        emit ISignalHub::instance().questionReceived(json);
    }

   IChatWidget* addChat() {
       auto chat  = new IChatWidget;
       chatsContainer->addWidget(chat);

       emit ISignalHub::instance().newChatAdded(chatsContainer->count());

       return chat;
    }

   IChatWidget* currentChat() {
       return qobject_cast<IChatWidget*>(chatsContainer->currentWidget());
   }

signals:


private:
    void setupUI() {

        mainLayout = new QVBoxLayout;
        setLayout(mainLayout);

        chatsContainer = new QStackedWidget;

        mainLayout->addWidget(chatsContainer);

        mainLayout->addWidget(new ILineEdit);
    }


private:


    QVBoxLayout* mainLayout;
    QStackedWidget* chatsContainer;
    ILineEdit* lineEdit;
};

#endif // ICHATSPAGE_H
