#ifndef CHATBOT_H
#define CHATBOT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class IChatBot : public QObject
{
    Q_OBJECT

public:

    enum Status {Waiting, Requesting, Receiving, Finished };

    explicit IChatBot(QObject *parent = nullptr);
    ~IChatBot();

    void reply(const QJsonObject &json);

    Status status() const { return m_status; }

signals:
    void replyReceived(QString);
    void finished();

public:
    void readResponseData();
    void abort();
    void finish();

private:
    QNetworkAccessManager *manager;
    QNetworkReply *m_reply;
    Status m_status;
};

#endif // CHATBOT_H
