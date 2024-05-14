#ifndef IHISTORYLIST_H
#define IHISTORYLIST_H

#include <QListWidget>
#include <QPushButton>
#include <QStyledItemDelegate>

class CustomItemDelegate : public QStyledItemDelegate {
public:
    CustomItemDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    inline QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override
    {
        QSize size = QStyledItemDelegate::sizeHint(option, index);
        size.setHeight(32);
        return size;
    }
};


class IHistoryList : public QListWidget {
public:
    IHistoryList(QWidget *parent = nullptr);

protected:

    void mouseMoveEvent(QMouseEvent* event) override;



private:
    void initButtonsWidget();

    void setSubGeometry(const QRect& rect, int i);

    QPushButton* getSubButton(int i);

    void addSubButton(const QString& icon, const QString &tooltip = "");

private:
    std::vector<QPushButton*> m_buttons;

};

#endif // IHISTORYLIST_H
