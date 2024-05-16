#ifndef CHATITEMDELEGATE_H
#define CHATITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QFont>
#include <QTextDocument>

class IChatItemDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit IChatItemDelegate(QObject *parent = nullptr);;
    void setItemHeight(const QModelIndex &index, int height);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    //QRect calculateMessageRect(const QRect &rightRect, int userHeight, const QString &message, const QFontMetrics &fontMetrics) const;
    void drawBackground(QPainter *painter, const QRect &rect) const;
private:
    QFont userFont;
    QFont textFont;
    int leftWidth;
    int userHeight;
    int iconMargin;
    int distance;
};


#endif // CHATITEMDELEGATE_H
