#include "chatbot.h"
#include <QUrl>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

ChatBot::ChatBot(QObject *parent) : QObject(parent) {
    manager = new QNetworkAccessManager(this);
}

void ChatBot::reply(std::string text) {
    QUrl url("http://localhost:11434/api/generate");

    QJsonObject json;
    json["model"] = "llama3";
    json["prompt"] = QString::fromStdString(text);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    m_reply = manager->post(request, QJsonDocument(json).toJson());
    QObject::connect(m_reply, &QNetworkReply::readyRead, this, &ChatBot::readResponseData);
}

void ChatBot::readResponseData() {
    QByteArray buffer = m_reply->readAll();
    if (buffer.isEmpty()) {
        qDebug() << "Empty response from server";
    }
    else {
        qDebug() << "Received response from server:" << buffer;
    }

    QJsonParseError error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(buffer, &error);

    if (error.error != QJsonParseError::NoError) {
        qDebug() << "Error parsing JSON:" << error.errorString();
        return;
    }

    if (!jsonDoc.isObject()) {
        qDebug() << "JSON data is not an object.";
        return;
    }

    QJsonObject jsonObject = jsonDoc.object();
    QString prompt = jsonObject.value("response").toString();
    qDebug() << "Received prompt from server:" << prompt;
    emit replyReceived(prompt);
}
