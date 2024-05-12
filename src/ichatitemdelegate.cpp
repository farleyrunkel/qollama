#include "ichatitemdelegate.h"
#include "ichatitemmodel.h"

#include <QPainter>

void IChatItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (!painter || !index.isValid()) {
        qDebug() << "Invalid painter or model index.";
        return;
    }

    drawBackground(painter, option.rect);

    QRect contRect = option.rect.adjusted(10, 0, -10, 0);
    contRect.setHeight(40);

    int leftWidth = 30;
    QRect leftRect = contRect.adjusted(0, 0, -contRect.width() + leftWidth, 0);
    QRect rightRect = contRect.adjusted(leftWidth, 0, -5, 0);

    QVariantMap chatData = index.data(Qt::DisplayRole).toMap();
    QIcon icon = qvariant_cast<QIcon>(chatData["icon"]);
    QString username = chatData["username"].toString();
    QString message = chatData["message"].toString();

    QPixmap iconPixmap = icon.pixmap(QSize(20, 20));
    painter->drawPixmap(leftRect.topLeft(), iconPixmap);

    int userHeight = 30;
    QRect usernameRect = rightRect.adjusted(0, 0, 0, -rightRect.height() + userHeight);
    painter->setFont(QFont("Arial", 10, QFont::Bold));
    painter->drawText(usernameRect, Qt::AlignLeft | Qt::AlignTop, username);

    QRect messageRect = calculateMessageRect(rightRect, userHeight, message, painter->fontMetrics());

    painter->setFont(QFont("Arial", 8));
    painter->drawText(messageRect, Qt::AlignLeft | Qt::AlignTop | Qt::TextWordWrap, message);
}

QSize IChatItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    QRect contRect = option.rect.adjusted(10, 0, -10, 0);
    contRect.setHeight(40);

    QRect messageRect = calculateMessageRect(contRect, 30, index.data(Qt::DisplayRole).toMap()["message"].toString(), QFontMetrics(QFont("Arial", 9)));

    int totalHeight = messageRect.height() + 30;

    size.setHeight(totalHeight + 10);
    return size;
}

void IChatItemDelegate::drawBackground(QPainter *painter, const QRect &rect) const {
    if (!painter) {
        qDebug() << "Invalid painter.";
        return;
    }

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(255, 255, 255));  // 背景色为白色
    painter->drawRect(rect);
    painter->restore();
}

QRect IChatItemDelegate::calculateMessageRect(const QRect &rightRect, int userHeight, const QString &message, const QFontMetrics &fontMetrics) const {
    QRect messageRect1 = rightRect.adjusted(0, userHeight, 0, 0);
    QRect messageRect = fontMetrics.boundingRect(messageRect1, Qt::AlignLeft | Qt::AlignTop | Qt::TextWordWrap, message);
    messageRect.setHeight(messageRect.height() + 5);
    return messageRect;
}
