#include "ichatitemdelegate.h"

#include <QPainter>
#include <QTextDocument>
#include <QStaticText>

IChatItemDelegate::IChatItemDelegate(QObject *parent)
    : leftWidth(34)
    , userHeight(30)
    , iconMargin(4)
    , userFont(QFont("Arial", 12, QFont::Bold))
    , textFont(QFont("Times", 12))
    , distance(10)
{
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

void IChatItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (!painter || !index.isValid()) {
        qDebug() << "Invalid painter or model index.";
        return;
    }

    this->drawBackground(painter, option.rect);

    QRect leftRect = option.rect.adjusted(0, 0, -option.rect.width() + leftWidth, 0);
    QRect usernameRect = option.rect.adjusted(leftWidth, 0, 0, -option.rect.height() + userHeight);
    QRect messageRect = option.rect.adjusted(leftWidth, userHeight, 0, 0);

    QVariantMap chatData = index.data(Qt::DisplayRole).toMap();
    QIcon icon = qvariant_cast<QIcon>(chatData["icon"]);
    QString username = chatData["username"].toString();
    QString message = chatData["message"].toString();

    // draw icon
    int iconPx = leftWidth - iconMargin * 2;
    QPixmap iconPixmap = icon.pixmap(QSize(iconPx, iconPx));
    painter->drawPixmap(leftRect.x() + iconMargin, leftRect.y() + iconMargin, iconPixmap);

    // draw username
    painter->setFont(userFont);
    QRect usernameAdjusted = usernameRect.adjusted(iconMargin, iconMargin, -iconMargin, 0);
    painter->drawText(usernameAdjusted, Qt::AlignLeft | Qt::AlignTop, username);

    // draw message
    painter->save();
    QRect messageAdjusted = messageRect.adjusted(iconMargin, 0, -iconMargin-10, 0);
    QTextDocument textDoc;
    textDoc.setDefaultFont(textFont);
    textDoc.setMarkdown(message);
    textDoc.setTextWidth(messageAdjusted.width());

    painter->translate(messageAdjusted.topLeft());
    textDoc.drawContents(painter);
    painter->translate(-messageAdjusted.topLeft());
    painter->restore();

    auto textSize = textDoc.size().toSize();
    messageRect.setHeight(textSize.height());

    QRect spaceAdjusted = messageRect.adjusted(0, messageRect.height(), 0, distance);
    this->drawBackground(painter, spaceAdjusted);
}


QSize IChatItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QSize hint = option.rect.size();

    auto message = index.data(Qt::DisplayRole).toMap()["message"].toString();
    QRect messageRect = option.rect.adjusted(leftWidth, userHeight, 0, 0);
    QRect messageAdjusted = messageRect.adjusted(iconMargin, 0, -iconMargin-10, 0);

    QTextDocument textDoc;
    textDoc.setMarkdown(message);
    textDoc.setDefaultFont(textFont);
    textDoc.setTextWidth(messageAdjusted.width());

    auto textSize = textDoc.size().toSize();

    hint.setHeight(userHeight + textSize.height() + distance);
    return hint;
}
