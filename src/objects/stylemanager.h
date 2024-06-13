#ifndef STYLEMANAGER_H
#define STYLEMANAGER_H

#include <QMap>
#include <QObject>
#include <QPainter>
#include <QPainterPath>

class StyleManager : public QObject {
    Q_OBJECT

public:
    static StyleManager& instance()  {
        static StyleManager instance;
        return instance;
    }

    void loadStyleSheet(const QString &filePath);
    void applyStyleSheet(QWidget *widget);
    void enableBorders(bool enable);
    static QPixmap roundedPixmap(const QPixmap &src);

    static void applyPalette(QWidget *widget);
private:
    QString replaceColors(const QString &styleSheet);
    QMap<QString, QString> parseColorPalette(const QString &styleSheet);
    QString addBorderStyles() const;

    QString currentStyleSheet;
    QMap<QString, QString> colorPalette;

    bool showBorders;

private:
    // Private constructor to prevent direct instantiation
    explicit StyleManager(QObject *parent = nullptr);

    // Delete copy constructor and assignment operator to prevent copying
    StyleManager(const StyleManager&) = delete;
    StyleManager& operator=(const StyleManager&) = delete;
};

#endif // STYLEMANAGER_H
