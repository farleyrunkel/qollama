#ifndef ISIGNALHUB_H
#define ISIGNALHUB_H

#include <QJsonObject>
#include <QObject>
#include "ichatscrollarea.h"

class SignalHub : public QObject {
    Q_OBJECT

public:
    static SignalHub &instance() {
        static SignalHub instance;
        return instance;
    }

signals:
    void generateRequest(const QJsonObject &);
    void listRequest();
    void listReceived(const QList<QString>);
    void on_message_sent(const QString &, bool isNewChat);
    void newChatAdded(IChatScrollArea *);
    void onExpandButtonClicked();
    void onNewChatButtonClicked();
    void onSideAreaHidden(bool);

private:
    SignalHub() {}
    SignalHub(const SignalHub &) = delete;
    SignalHub &operator=(const SignalHub &) = delete;
};

#endif // ISIGNALHUB_H
