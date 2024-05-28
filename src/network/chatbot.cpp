#include "chatbot.h"
#include <QUrl>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

IChatBot::IChatBot(QObject *parent)
    : QObject(parent)
    , manager(new QNetworkAccessManager(this))
    , m_reply(nullptr)
    , m_status(Waiting) {
}

IChatBot::~IChatBot() {

    if (m_reply) {
        m_reply->deleteLater();
    }
}

void IChatBot::reply(const QJsonObject& json) {
    QUrl url("http://localhost:11434/api/generate");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    m_reply = manager->post(request, QJsonDocument(json).toJson());
    m_status = Status::Requesting;

    QObject::connect(m_reply, &QNetworkReply::readyRead, this, &IChatBot::readResponseData);
    QObject::connect(m_reply, &QNetworkReply::finished, this, &IChatBot::finish);
    QObject::connect(m_reply, &QNetworkReply::errorOccurred, this, [&](QNetworkReply::NetworkError error){
        qDebug() << "Network error occurred:" << error;
        emit replyReceived("Network error occurred");
    });
}

void IChatBot::finish() {
    m_status = Status::Finished;
    emit finished();
}

void IChatBot::readResponseData() {
    m_status = Status::Receiving;
    QByteArray buffer = m_reply->readAll();
    if (buffer.isEmpty()) {
        qDebug() << "Empty response from server";
        return;
    }

    qDebug() << "Received response from server:" << buffer;

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

void IChatBot::abort() {
    if (m_reply) {
        m_reply->abort();
    }
}
