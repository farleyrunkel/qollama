#ifndef CHATBOT_H
#define CHATBOT_H

#include <QObject>
#include <string>
#include <QCoreApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QThread>


class ChatBot : public QObject
{
    Q_OBJECT
public:
    ChatBot(QObject *parent = nullptr);;

    void reply(std::string text = "");

signals:
    void replyReceived(QString);

private slots:
    void onFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
    QNetworkReply *m_reply;
};

inline ChatBot::ChatBot(QObject *parent) : QObject(parent) {
    // 创建一个 QNetworkAccessManager 实例
    manager = new QNetworkAccessManager(this);

    // 连接信号 finished，当请求完成时触发
    connect(manager, &QNetworkAccessManager::finished, this, &ChatBot::onFinished);
}


inline void ChatBot::reply(std::string text) {

    QUrl url("http://localhost:11434/api/generate");

    QJsonObject json;
    json["model"] = "llama3";
    json["prompt"] = QString::fromStdString(text);
    // json["stream"] = false;
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, QJsonDocument(json).toJson());
}

inline void ChatBot::onFinished(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        // 请求成功，读取响应数据并发送信号
        QByteArray responseData = reply->readAll();

        QByteArray str;
        // 根据换行符分割 QByteArray，并将每个部分添加到 jsonDataList 中
        QByteArray currentData;
        for (char byte : responseData) {
            str.append( byte);
            if (byte == '\n') {
                qDebug() << "\n";
                qDebug() << str;


                QJsonParseError error;
                QJsonDocument jsonDoc = QJsonDocument::fromJson(str, &error);

                if (error.error != QJsonParseError::NoError) {
                    qDebug() << "Error parsing JSON q:" << error.errorString();
                    return;
                }

                if (!jsonDoc.isObject()) {
                    qDebug() << "JSON data is not an object.";
                    return;
                }


                QJsonObject jsonObject = jsonDoc.object();

                // 现在可以使用 jsonObject 对象中的数据了
                QString prompt = jsonObject.value("response").toString();
                // qDebug() << prompt;
                emit replyReceived(prompt);
                str.clear();

                // QThread::sleep(1); // 1000 毫秒 = 1 秒

            }
        }

    } else {
        // 请求失败，输出错误信息
        qDebug() << "Error:" << reply->errorString();
    }

    // 释放资源
    reply->deleteLater();
}


#endif // CHATBOT_H
