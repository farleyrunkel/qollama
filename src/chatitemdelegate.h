#ifndef CHATITEMDELEGATE_H
#define CHATITEMDELEGATE_H

#include <QStyledItemDelegate>

class ChatItemDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    void setItemHeight(const QModelIndex &index, int height);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
private:
    QRect calculateMessageRect(const QRect &rightRect, int userHeight, const QString &message, const QFontMetrics &fontMetrics) const;
    void drawBackground(QPainter *painter, const QRect &rect) const;
};


#endif // CHATITEMDELEGATE_H
