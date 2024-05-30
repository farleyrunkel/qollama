#include "StyleManager.h"
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QWidget>

StyleManager::StyleManager(QObject *parent) : QObject(parent) {
}

void StyleManager::loadStyleSheet(const QString &filePath) {
    QFile file(filePath);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString styleSheet = stream.readAll();
        file.close();

        // Parse the color palette from the QSS comments
        colorPalette = parseColorPalette(styleSheet);

        // Replace color variables with actual values
        currentStyleSheet = replaceColors(styleSheet);
    }
}

void StyleManager::applyStyleSheet(QWidget *widget) {
    widget->setStyleSheet(currentStyleSheet);
}

QString StyleManager::replaceColors(const QString &styleSheet) {
    QString newStyleSheet = styleSheet;

    QRegularExpression regex(R"(\s([^\s;]+)\s*;\s*/\*\s*@(\w+)\s*\*/)");

    QRegularExpressionMatchIterator it = regex.globalMatch(styleSheet);
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        if (match.hasMatch()) {
            QString fullMatch = match.captured();

            QString placeHolder = match.captured(1);
            QString color = match.captured(2);
            QString newFullMatch = fullMatch.replace(placeHolder, colorPalette[color]);

            newStyleSheet.replace(match.captured(), newFullMatch);
        }
    }
    return newStyleSheet;
}

QMap<QString, QString> StyleManager::parseColorPalette(const QString &styleSheet) {
    QMap<QString, QString> palette;
    QRegularExpression regex(R"(@(\w+):\s*#([0-9a-fA-F]{6});\s*\(\d{1,3},\s*\d{1,3},\s*\d{1,3}\)\s*)");
    QRegularExpressionMatchIterator it = regex.globalMatch(styleSheet);

    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        if (match.hasMatch()) {
            QString name = match.captured(1);
            QString color = "#" + match.captured(2);
            palette[name] = color;
        }
    }
    return palette;
}
