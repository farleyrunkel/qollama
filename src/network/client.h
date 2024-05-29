#ifndef OLLAMACLIENT_H
#define OLLAMACLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace ollama {

class Client : public QObject
{
    Q_OBJECT

public:

    enum Status {Waiting, Requesting, Receiving, Finished };

    explicit Client(QObject *parent = nullptr);
    ~Client();

    void generate(const QJsonObject &json);
    void chat(const QJsonObject &json);
    void embeddings(const QJsonObject &json);
    void pull(const QJsonObject &json);
    void push(const QJsonObject &json);

    Status status() const;

signals:
    void replyReceived(QString);
    void finished();

public:
    void readResponseData();
    void abort();
    void onFinished();

private:
    void sendRequest(const QString &url, const QJsonObject &json);

private:
    QNetworkAccessManager *m_manager;
    QNetworkReply *m_reply;
    Status m_status;
};
}
#endif // OLLAMACLIENT_H
