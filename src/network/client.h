#ifndef OLLAMACLIENT_H
#define OLLAMACLIENT_H

#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>

namespace ollama {

class Client : public QObject {
    Q_OBJECT

public:
    enum Status { Waiting, Requesting, Receiving, Finished };

    explicit Client(QObject *parent = nullptr);
    ~Client();

    void generate(const QJsonObject &json);
    void chat(const QJsonObject &json);
    void embeddings(const QJsonObject &json);
    void pull(const QJsonObject &json);
    void push(const QJsonObject &json);
    void list();

    void abort() { m_manager->disconnect(); }
    Status status() const;

signals:
    void replyReceived(const QString &);
    void finished();

    void listReceived(const QList<QString> &);

private:
    QNetworkReply *sendRequest(const QString &url,
                               const QJsonObject &json = QJsonObject());

private:
    QNetworkAccessManager *m_manager;
    Status m_status;

    QJsonObject m_modelList;
};
} // namespace ollama
#endif // OLLAMACLIENT_H
