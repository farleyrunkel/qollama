#ifndef STYLEMANAGER_H
#define STYLEMANAGER_H

#include <QObject>
#include <QString>
#include <QMap>

class StyleManager : public QObject {
    Q_OBJECT

public:
    explicit StyleManager(QObject *parent = nullptr);

    void loadStyleSheet(const QString &filePath);
    void applyStyleSheet(QWidget *widget);

    void setModifyQssFile(bool isModified = true) {

    }

private:

    QString replaceColors(const QString &styleSheet);
    QMap<QString, QString> parseColorPalette(const QString &styleSheet);

private:

    QString currentStyleSheet;
    QMap<QString, QString> colorPalette;
};

#endif // STYLEMANAGER_H
