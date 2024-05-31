#include "client.h"
#include <QUrl>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include "isignalhub.h"

namespace ollama {

Client::Client(QObject *parent)
    : QObject(parent)
    , m_manager(new QNetworkAccessManager(this))
    , m_reply(nullptr)
    , m_status(Waiting) {

   connect(&ISignalHub::instance(), &ISignalHub::questionReceived, this, &Client::generate);

}

Client::~Client() {

    if (m_reply) {
        m_reply->deleteLater();
    }
}

void Client::chat(const QJsonObject& json) {
    sendRequest("http://localhost:11434/api/chat", json);
}

void Client::generate(const QJsonObject& json) {
    sendRequest("http://localhost:11434/api/generate", json);
}

void Client::embeddings(const QJsonObject& json) {
    sendRequest("http://localhost:11434/api/embeddings", json);
}

void Client::pull(const QJsonObject& json) {
    sendRequest("http://localhost:11434/api/pull", json);
}

void Client::push(const QJsonObject& json) {
    sendRequest("http://localhost:11434/api/push", json);
}

Client::Status Client::status() const {
    return m_status;
}

void Client::sendRequest(const QString &url, const QJsonObject& json) {

    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setUrl(QUrl(url));

    m_reply = m_manager->post(request, QJsonDocument(json).toJson());
    m_status = Status::Requesting;

    QObject::connect(m_reply, &QNetworkReply::readyRead, this, &Client::readResponseData);
    QObject::connect(m_reply, &QNetworkReply::finished, this, &Client::onFinished);
    QObject::connect(m_reply, &QNetworkReply::errorOccurred, [&](QNetworkReply::NetworkError){
        emit replyReceived("Network error occurred");
    });
}

void Client::onFinished() {
    m_status = Status::Finished;
    emit finished();
}

void Client::readResponseData() {
    m_status = Status::Receiving;
    QByteArray buffer = m_reply->readAll();
    if (buffer.isEmpty()) {
        qDebug() << "Empty response from server";
        return;
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

    auto response = jsonDoc.object().value("response");
    emit replyReceived(response.toString());
}

void Client::abort() {
    if (m_reply) {
        m_reply->abort();
    }
}

}
