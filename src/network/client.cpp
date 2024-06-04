#include "client.h"
#include <QUrl>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include "signalhub.h"

namespace ollama {

Client::Client(QObject *parent)
    : QObject(parent)
    , m_manager(new QNetworkAccessManager(this))
    , m_status(Waiting) {

    connect(&SignalHub::instance(), &SignalHub::generateRequest, this, &Client::generate);
    connect(&SignalHub::instance(), &SignalHub::listRequest, this, &Client::list);
}

Client::~Client() {
    qDebug() << "Client destroyed.";
}

void Client::chat(const QJsonObject& json) {
    qDebug() << "Chat request with JSON:" << QJsonDocument(json).toJson(QJsonDocument::Compact);
    sendRequest("http://localhost:11434/api/chat", json);
}

void Client::generate(const QJsonObject& json) {
    qDebug() << "Generate request with JSON:" << QJsonDocument(json).toJson(QJsonDocument::Compact);
    auto reply = sendRequest("http://localhost:11434/api/generate", json);

    QObject::connect(reply, &QNetworkReply::readyRead, this, [this, reply]() {
        m_status = Status::Receiving;
        qDebug() << "Receiving response. Status:" << m_status;

        QByteArray buffer = reply->readAll();
        if (buffer.isEmpty()) {
            qDebug() << "Empty response from server";
            return;
        }

        qDebug() << "Response buffer:" << buffer;

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
        qDebug() << "Parsed response:" << response.toString();
        emit replyReceived(response.toString());
    });

    QObject::connect(reply, &QNetworkReply::finished, this, [this]() {
        m_status = Status::Finished;
        qDebug() << "Request finished. Status:" << m_status;
        emit finished();
    });

    QObject::connect(reply, &QNetworkReply::errorOccurred, this, [this](QNetworkReply::NetworkError error){
        qDebug() << "Network error occurred:" << error;
        emit replyReceived("Network error occurred");
    });
}

void Client::embeddings(const QJsonObject& json) {
    qDebug() << "Embeddings request with JSON:" << QJsonDocument(json).toJson(QJsonDocument::Compact);
    sendRequest("http://localhost:11434/api/embeddings", json);
}

void Client::pull(const QJsonObject& json) {
    qDebug() << "Pull request with JSON:" << QJsonDocument(json).toJson(QJsonDocument::Compact);
    sendRequest("http://localhost:11434/api/pull", json);
}

void Client::push(const QJsonObject& json) {
    qDebug() << "Push request with JSON:" << QJsonDocument(json).toJson(QJsonDocument::Compact);
    sendRequest("http://localhost:11434/api/push", json);
}

void Client::list() {
    qDebug() << "Tags request.";
    auto reply = sendRequest("http://localhost:11434/api/tags");
    QObject::connect(reply, &QNetworkReply::readyRead, this, [this, reply]() {
        m_status = Status::Receiving;
        // todo: finish get list from ollama

        QList<QString> list = {"Gemma", "codellama", "ChatGPT-4o", "llama3"};
        emit SignalHub::instance().listReceived(list);
    });

    QObject::connect(reply, &QNetworkReply::finished, this, [this]() {
        m_status = Status::Finished;
        qDebug() << "Request finished. Status:" << m_status;
        emit finished();
    });

    QObject::connect(reply, &QNetworkReply::errorOccurred, this, [this](QNetworkReply::NetworkError error){
        qDebug() << "Network error occurred:" << error;
        emit replyReceived("Network error occurred");
    });
}

Client::Status Client::status() const {
    qDebug() << "Status requested:" << m_status;
    return m_status;
}

QNetworkReply* Client::sendRequest(const QString &url, const QJsonObject& json) {
    qDebug() << "Sending request to URL:" << url << "with JSON:" << QJsonDocument(json).toJson(QJsonDocument::Compact);

    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setUrl(QUrl(url));

    m_status = Status::Requesting;
    qDebug() << "Request status:" << m_status;

    auto reply = m_manager->post(request, QJsonDocument(json).toJson());
    qDebug() << "Request sent.";
    return reply;
}

} // namespace ollama
