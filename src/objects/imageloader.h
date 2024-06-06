#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QPixmap>
#include <QUrl>

class ImageLoader : public QObject {
    Q_OBJECT

public:
    explicit ImageLoader(QObject *parent = nullptr); // Constructor

    void loadImage(const QUrl &url); // Load image from URL

    static QPixmap
    circularPixmap(const QPixmap &source); // Convert to circular pixmap

signals:
    void imageLoaded(QPixmap *pixmap); // Signal emitted when image is loaded

private slots:
    void
    onFinished(QNetworkReply *reply); // Slot to handle finished network request

private:
    QPixmap *m_pixmap;               // Loaded pixmap
    QNetworkAccessManager m_manager; // Network manager for loading images
};

#endif // IMAGELOADER_H
