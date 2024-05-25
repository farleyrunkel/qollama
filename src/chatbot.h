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

    void reply(const QMap<QString, QString> &map);

    Status status() const { return m_status; } // 更正getter函数

signals:
    void replyReceived(QString);
    void finished();

public slots:
    void readResponseData();
    void abort();
    void finish();

private:
    QNetworkAccessManager *manager;
    QNetworkReply *m_reply;
    Status m_status; // 更正成员变量的名字以避免混淆
};

#endif // CHATBOT_H
