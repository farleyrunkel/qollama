#include "stylemanager.h"
#include <QFile>
#include <QRegularExpression>
#include <QTextStream>
#include <QWidget>

StyleManager::StyleManager(QObject *parent)
    : QObject(parent), showBorders(false) {}

void StyleManager::loadStyleSheet(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Failed to open file for reading:" << filePath;
        return;
    }

    QTextStream stream(&file);
    QString styleSheet = stream.readAll();
    file.close();

    // Parse the color palette from the QSS comments
    colorPalette = parseColorPalette(styleSheet);

    // Replace color variables with actual values
    currentStyleSheet = replaceColors(styleSheet);

    if (showBorders) {
        currentStyleSheet += addBorderStyles();
    }
}

void StyleManager::applyPalette(QWidget *widget) {
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::white);
    palette.setColor(QPalette::WindowText, Qt::black);
    palette.setColor(QPalette::Base, Qt::white);
    palette.setColor(QPalette::AlternateBase, QColor(225, 225, 225));
    palette.setColor(QPalette::ToolTipBase, Qt::white);
    palette.setColor(QPalette::ToolTipText, Qt::black);
    palette.setColor(QPalette::Text, Qt::black);
    palette.setColor(QPalette::Button, QColor(240, 240, 240));
    palette.setColor(QPalette::ButtonText, Qt::black);
    palette.setColor(QPalette::BrightText, Qt::red);
    palette.setColor(QPalette::Link, QColor(42, 130, 218));
    palette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    palette.setColor(QPalette::HighlightedText, Qt::white);

    widget->setPalette(palette);
}


void StyleManager::applyStyleSheet(QWidget *widget) {
    widget->setStyleSheet(currentStyleSheet);
}

QString StyleManager::replaceColors(const QString &styleSheet) {
    QString newStyleSheet = styleSheet;

    QRegularExpression regex(R"([\s:]([^\s;]+)\s*;\s*/\*\s*@(\w+)\s*\*/)");

    QRegularExpressionMatchIterator it = regex.globalMatch(styleSheet);
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        if (match.hasMatch()) {
            QString fullMatch = match.captured();

            QString placeHolder = match.captured(1);
            QString color = match.captured(2);
            QString newFullMatch =
                fullMatch.replace(placeHolder, colorPalette[color]);

            newStyleSheet.replace(match.captured(), newFullMatch);
        }
    }
    return newStyleSheet;
}

QMap<QString, QString>
StyleManager::parseColorPalette(const QString &styleSheet) {
    QMap<QString, QString> palette;
    QRegularExpression regex(
        R"(@(\w+):\s*#([0-9a-fA-F]{6});\s*\(\d{1,3},\s*\d{1,3},\s*\d{1,3}\)\s*)");
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

void StyleManager::enableBorders(bool enable) {
    showBorders = enable;
    if (showBorders) {
        currentStyleSheet += addBorderStyles();
    } else {
        // Remove border styles if they exist
        QRegularExpression borderRegex(
            R"((\*|QWidget)[^{}]*{[^{}]*border:[^{}]*}[^{}]*)");
        currentStyleSheet.remove(borderRegex);
    }
}

QPixmap StyleManager::roundedPixmap(const QPixmap &src) {

    int size = qMin(src.width(), src.height());
    int radius = size / 2;

    QPixmap dest(size, size);
    dest.fill(Qt::transparent);

    QPainter painter(&dest);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QPainterPath path;
    path.addEllipse(0, 0, size, size);

    painter.setClipPath(path);

    int x = (size - src.width()) / 2;
    int y = (size - src.height()) / 2;

    painter.drawPixmap(x, y, src);

    return dest;
}

QString StyleManager::addBorderStyles() const {
    return R"(
    * {
        border: 1px solid red;
    }
    )";
}
