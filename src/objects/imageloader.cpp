#include "imageloader.h"
#include <QDebug>
#include <QPainter>
#include <QPainterPath>

ImageLoader::ImageLoader(QObject *parent) : QObject(parent), m_pixmap(nullptr) {
    loadImage(QUrl("https://picsum.photos/200")); // Load default image
    connect(&m_manager, &QNetworkAccessManager::finished, this,
            &ImageLoader::onFinished);
}

void ImageLoader::loadImage(const QUrl &url) {
    m_manager.get(QNetworkRequest(url)); // Request image from URL
}

QPixmap ImageLoader::circularPixmap(const QPixmap &source) {
    QPixmap circularPixmap(source.size());
    circularPixmap.fill(Qt::transparent); // Create transparent pixmap

    QPainter painter(&circularPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    QPainterPath path;
    path.addEllipse(0, 0, source.width(), source.height());
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, source);

    return circularPixmap;
}

void ImageLoader::onFinished(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray imageData = reply->readAll();
        m_pixmap = new QPixmap();
        m_pixmap->loadFromData(imageData); // Load pixmap from network data

        emit imageLoaded(m_pixmap); // Emit signal with loaded pixmap
    } else {
        qDebug() << "Failed to load image:" << reply->errorString();
    }
    reply->deleteLater(); // Clean up network reply
}
