#ifndef STYLEMANAGER_H
#define STYLEMANAGER_H

#include <QMap>
#include <QObject>
#include <QPainter>
#include <QPainterPath>

class StyleManager : public QObject {
    Q_OBJECT

public:
    explicit StyleManager(QObject *parent = nullptr);

    void loadStyleSheet(const QString &filePath);
    void applyStyleSheet(QWidget *widget);
    void enableBorders(bool enable);
    static QPixmap roundedPixmap(const QPixmap &src);

private:
    QString replaceColors(const QString &styleSheet);
    QMap<QString, QString> parseColorPalette(const QString &styleSheet);
    QString addBorderStyles() const;

    QString currentStyleSheet;
    QMap<QString, QString> colorPalette;

    bool showBorders;
};

#endif // STYLEMANAGER_H
