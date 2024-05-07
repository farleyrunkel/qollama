#ifndef IHISTORYLIST_H
#define IHISTORYLIST_H

#include <QWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMenu>
#include <QSpacerItem>
#include <QShowEvent>
#include <QStyledItemDelegate>

class CustomItemDelegate : public QStyledItemDelegate {
public:
    CustomItemDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override
    {
        QSize size = QStyledItemDelegate::sizeHint(option, index);
        size.setHeight(32); // 设置item的高度为50像素
        return size;
    }

    // void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
    //     QStyledItemDelegate::paint(painter, option, index);

    //     QRect rect = option.rect;

    //     QRect buttonRect1 = QRect(rect.right() - 60, rect.top() + 2, 30, 30);

    //     painter->setBrush(Qt::red);
    //     painter->drawRect(buttonRect1);

    //     QRect buttonRect2 = QRect(rect.right() - 30, rect.top() + 2, 30, 30);

    //     painter->setBrush(Qt::blue);
    //     painter->drawRect(buttonRect2);
    // }
};


class IHistoryList : public QListWidget {
public:
    IHistoryList(QWidget *parent = nullptr) : QListWidget(parent) {}

protected:
    void showEvent(QShowEvent *event) override {
        QListWidget::showEvent(event);
        initButtonsWidget();
        setIconSize(QSize(100, 100)); // 设置item中的图标大小
        setItemDelegate(new CustomItemDelegate);
        setObjectName("historyList");
        setUniformItemSizes(true);
    }
    void mouseMoveEvent(QMouseEvent* event) override {

        auto index = this->indexAt(event->pos());

        if (index.isValid()) {
            auto item_rect = this->visualRect(index);

            // 设置按钮的位置
            widget->setGeometry(item_rect);
            widget->setVisible(true);
        }
    }
private:
    void initButtonsWidget() {
        widget = new QWidget(this);
        QHBoxLayout *layout = new QHBoxLayout(widget);

        QPushButton *moreButton = createButton(":/icon/more-horiz.svg", "More");
        QPushButton *archButton = createButton(":/icon/archive-book.svg", "Archive");

        QMenu *menu = new QMenu(moreButton);
        menu->addAction("Share");
        menu->addAction("Rename");
        menu->addAction("Delete chat");
        moreButton->setMenu(menu);

        layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
        layout->addWidget(moreButton);
        layout->addWidget(archButton);

        widget->setLayout(layout);
        widget->setObjectName("buttonsWidget");
        widget->setStyleSheet("background: rgba(255, 255, 255, 128);");
        widget->setVisible(false);
    }

    QPushButton *createButton(const QString &iconPath, const QString &tooltip) {
        QPushButton *button = new QPushButton(QIcon(iconPath), "");
        button->setFixedSize(QSize(16, 16));
        button->setToolTip(tooltip);
        button->setFlat(true);
        return button;
    }
private:
    QWidget *widget;
};

#endif // IHISTORYLIST_H
