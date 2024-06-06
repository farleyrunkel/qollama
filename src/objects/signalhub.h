#ifndef ISIGNALHUB_H
#define ISIGNALHUB_H

#include <QObject>
#include <QJsonObject>
#include <ichatwidget.h>

class SignalHub : public QObject
{
    Q_OBJECT

public:
    static SignalHub& instance()
    {
        static SignalHub instance;
        return instance;
    }

signals:
    void generateRequest(const QJsonObject&);
    void listRequest();
    void listReceived(const QList<QString>);
    void on_message_sent(const QString&, bool isNewChat);
    void newChatAdded(IChatWidget *);
    void onExpandButtonClicked();
    void onSideAreaHidden(bool);
private:
    SignalHub() {}
    SignalHub(const SignalHub&) = delete;
    SignalHub& operator=(const SignalHub&) = delete;
};


#endif // ISIGNALHUB_H
