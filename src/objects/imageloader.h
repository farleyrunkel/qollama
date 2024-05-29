#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QApplication>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>
#include <QFile>
#include <QTextStream>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>

class ImageLoader : public QObject
{
    Q_OBJECT

public:
    ImageLoader(QObject *parent = nullptr)
        : QObject(parent), pixmap(nullptr)
    {
        loadImage(QUrl("https://picsum.photos/200"));
        connect(&manager, &QNetworkAccessManager::finished, this, &ImageLoader::onFinished);
    }

    void loadImage(const QUrl &url)
    {
        manager.get(QNetworkRequest(url));
    }

    static QPixmap circularPixmap(const QPixmap &source)
    {
        QPixmap circularPixmap(source.size());
        circularPixmap.fill(Qt::transparent);

        QPainter painter(&circularPixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);

        QPainterPath path;
        path.addEllipse(0, 0, source.width(), source.height());
        painter.setClipPath(path);
        painter.drawPixmap(0, 0, source);

        return circularPixmap;
    };

signals:
    void imageLoaded(QPixmap *pixmap);

private slots:
    void onFinished(QNetworkReply *reply)
    {
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray imageData = reply->readAll();
            pixmap = new QPixmap();
            pixmap->loadFromData(imageData);

            emit imageLoaded(pixmap);
        }
        else
        {
            qDebug() << "Failed to load image:" << reply->errorString();
        }
        reply->deleteLater();
    }

private:
    QPixmap *pixmap;
    QNetworkAccessManager manager;
};

#endif // IMAGELOADER_H
