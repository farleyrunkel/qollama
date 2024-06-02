#ifndef ISIGNALHUB_H
#define ISIGNALHUB_H

#include <QObject>
#include <QJsonObject>

class ISignalHub : public QObject
{
    Q_OBJECT

public:
    static ISignalHub& instance()
    {
        static ISignalHub instance;
        return instance;
    }

signals:
    void generateRequest(const QJsonObject&);
    void listRequest();
    void listReceived(const QList<QString>);
    void on_IVPushCard_clicked(const QString&) ;
    void newChatAdded(int);

private:
    ISignalHub() {}
    ISignalHub(const ISignalHub&) = delete;
    ISignalHub& operator=(const ISignalHub&) = delete;
};


#endif // ISIGNALHUB_H
