#include "client.h"
#include "configmanager.h"
#include "signalhub.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>
#include <QJsonArray>
namespace ollama {

Client::Client(QObject *parent)
    : QObject(parent), m_manager(new QNetworkAccessManager(this)),
    m_status(Waiting) {

    connect(&SignalHub::instance(), &SignalHub::generateRequest, this,
            &Client::generate);
    connect(&SignalHub::instance(), &SignalHub::listRequest, this, &Client::list);
    connect(&SignalHub::instance(), &SignalHub::disconnect, this,
            &Client::disconnect);
    connect(&SignalHub::instance(), &SignalHub::chatRequest, this,
            &Client::chat);
}

Client::~Client() { qDebug() << "Client destroyed."; }

QString Client::url() {
    return ConfigManager::instance().config("ollamaport").toString();
}

void Client::chat(const QJsonObject &json) {
    sendRequestAndProcessResponse("chat", json, [this](const QJsonObject &response) {
        auto content = response.value("message").toObject().value("content").toString();
        qDebug() << "Parsed chat response:" << content;
        emit replyReceived(content);
    });
}

void Client::generate(const QJsonObject &json) {
    sendRequestAndProcessResponse("generate", json, [this](const QJsonObject &response) {
        auto content = response.value("response").toString();
        qDebug() << "Parsed generate response:" << content;
        emit replyReceived(content);
    });
}

void Client::list() {
    sendRequestAndProcessResponse("tags", QJsonObject(), [this](const QJsonObject &response) {
        QJsonArray modelsArray = response.value("models").toArray();
        QList<QString> list;

        for (const QJsonValue &value : modelsArray) {
            if (value.isObject()) {
                QString name = value.toObject().value("name").toString();
                if (!name.isEmpty()) {
                    list.append(name);
                }
            }
        }

        emit SignalHub::instance().listReceived(list);
    });
}

void Client::sendRequestAndProcessResponse(const QString &endpoint, const QJsonObject &json, std::function<void(const QJsonObject&)> processResponse) {
    auto reply = sendRequest(QString("http://%1/api/%2").arg(url()).arg(endpoint), json);

    QObject::connect(reply, &QNetworkReply::readyRead, this, [this, reply, processResponse]() {
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

        auto response = jsonDoc.object();

        processResponse(response);
    });

    QObject::connect(reply, &QNetworkReply::finished, this, [this]() {
        m_status = Status::Finished;
        qDebug() << "Request finished. Status:" << m_status;
        emit finished();
    });

    QObject::connect(reply, &QNetworkReply::errorOccurred, this,
                     [this](QNetworkReply::NetworkError error) {
                         qDebug() << "Network error occurred:" << error;
                         emit errorOccurred("Network error occurred");
                     });
}


void Client::embeddings(const QJsonObject &json) {
    qDebug() << "Embeddings request with JSON:"
             << QJsonDocument(json).toJson(QJsonDocument::Compact);
    sendRequest("http://localhost:11434/api/embeddings", json);
}

void Client::pull(const QJsonObject &json) {
    qDebug() << "Pull request with JSON:"
             << QJsonDocument(json).toJson(QJsonDocument::Compact);
    sendRequest("http://localhost:11434/api/pull", json);
}

void Client::push(const QJsonObject &json) {
    qDebug() << "Push request with JSON:"
             << QJsonDocument(json).toJson(QJsonDocument::Compact);
    sendRequest("http://localhost:11434/api/push", json);
}

Client::Status Client::status() const {
    qDebug() << "Status requested:" << m_status;
    return m_status;
}

QNetworkReply *Client::sendRequest(const QString &url,
                                   const QJsonObject &json) {
    m_status = Status::Requesting;
    qDebug() << "Sending request to URL:" << url << "with JSON:"
             << QJsonDocument(json).toJson(QJsonDocument::Compact);

    QNetworkRequest request;
    request.setUrl(QUrl(url));

    QNetworkReply* reply;

    if(!json.empty()) {
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        reply = m_manager->post(request, QJsonDocument(json).toJson());
    }
    else {
        reply = m_manager->get(request);
        qDebug() << " m_manager->get request:" << request.url() ;
    }

    qDebug() << "Request sent.";
    return reply;
}

} // namespace ollama
