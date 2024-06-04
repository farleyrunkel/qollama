#ifndef STYLEMANAGER_H
#define STYLEMANAGER_H

#include <QObject>
#include <QMap>

class QWidget;

class IStyleManager : public QObject {
    Q_OBJECT

public:
    explicit IStyleManager(QObject *parent = nullptr);

    void loadStyleSheet(const QString &filePath);
    void applyStyleSheet(QWidget *widget);
    void enableBorders(bool enable);

private:
    QString replaceColors(const QString &styleSheet);
    QMap<QString, QString> parseColorPalette(const QString &styleSheet);
    QString addBorderStyles() const;

    QString currentStyleSheet;
    QMap<QString, QString> colorPalette;
    bool showBorders;
};

#endif // STYLEMANAGER_H
