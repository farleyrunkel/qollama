#ifndef IHISTORYLIST_H
#define IHISTORYLIST_H

#include <QListWidget>
#include <QPushButton>
#include <QStyledItemDelegate>
#include <QPainter>

class IHistoryItemDelegate : public QStyledItemDelegate {
public:
    IHistoryItemDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {
        qDebug() << "CustomItemDelegate created";
    }

    inline QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override {
        QSize size = QStyledItemDelegate::sizeHint(option, index);
        size.setHeight(32); // Set fixed height to 32
        return size;
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        QStyledItemDelegate::paint(painter, option, index);
        if (!painter || !index.isValid()) {
            qDebug() << "Invalid painter or model index.";
            return;
        }

        auto rec = option.rect;
        rec.setWidth(option.widget->width()); // Adjust rect width to widget width

        // Get the text to be drawn
        auto text = index.data(Qt::ToolTipRole).toString();

        // Generate elided text to fit available width
        QString elidedText = painter->fontMetrics().elidedText(text, Qt::ElideRight, rec.width() - 10);

        // Set font
        painter->setFont(QFont("Arial", 8));

        // Draw text
        painter->drawText(rec, Qt::AlignLeft | Qt::AlignVCenter, elidedText);
    }
};

class IHistoryList : public QListWidget {
    Q_OBJECT

public:
    IHistoryList(QWidget *parent = nullptr);


protected:
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    void setupUI();
    void setSubGeometry(const QRect& rect, int i);
    QPushButton* getSubButton(int i);
    QPushButton * addButton(const QString& icon, const QString &tooltip = "");
    void deleteChat(bool checked);

signals:
    void itemDeleted(int);

private:
    std::vector<QPushButton*> m_buttons;
    QModelIndex curr_index;
};

#endif // IHISTORYLIST_H
