#ifndef IHISTORYLIST_H
#define IHISTORYLIST_H

#include <QWidget>
#include <QListWidgetItem >
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QObject>
#include "ioverlaybutton.h"
#include <QMenu>
#include <QStyledItemDelegate>
// 自定义委托类

#include <QStyledItemDelegate>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMenu>
#include <QStandardItemModel>
#include <QStandardItem>

class CustomItemDelegate : public QStyledItemDelegate {
public:
    CustomItemDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    // 重写sizeHint函数，设置item的大小
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override
    {
        QSize size = QStyledItemDelegate::sizeHint(option, index);
        size.setHeight(32); // 设置item的高度为50像素
        return size;
    }

    // void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
    //     QStyledItemDelegate::paint(painter, option, index);

    //     // 获取单元格的矩形区域
    //     QRect rect = option.rect;

    //     // 计算第一个按钮的矩形区域
    //     QRect buttonRect1 = QRect(rect.right() - 60, rect.top() + 2, 30, 30);

    //     // 绘制第一个按钮
    //     painter->setBrush(Qt::red);
    //     painter->drawRect(buttonRect1);

    //     // 计算第二个按钮的矩形区域
    //     QRect buttonRect2 = QRect(rect.right() - 30, rect.top() + 2, 30, 30);

    //     // 绘制第二个按钮
    //     painter->setBrush(Qt::blue);
    //     painter->drawRect(buttonRect2);
    // }

};

class IHistoryList: public QListWidget
{

public:

    using QListWidget::QListWidget;

public:

    void mouseMoveEvent(QMouseEvent* event) override {

        auto index = this->indexAt(event->pos());

        if (index.isValid()) {
            auto item_rect = this->visualRect(index);

            // 设置按钮的位置
            widget->setGeometry(item_rect);
            widget->setVisible(true);
        }
    }


public:

    void showEvent(QShowEvent* event) override {
        QListWidget::showEvent(event);
        initButtonsWidget();
    }

    void initButtonsWidget() {

        widget = new QWidget(this);

        QHBoxLayout *layout = new QHBoxLayout;
        QPushButton *moreButton = new QPushButton(QIcon("://icon/more-horiz.svg"), "");
        moreButton->setFixedSize(QSize(16, 16));
        moreButton->setToolTip("More");
        QPushButton *archButton = new QPushButton(QIcon("://icon/archive-book.svg"), "");
        archButton->setFixedSize(QSize(16, 16));
        archButton->setToolTip("Archive");
        archButton->setFlat(true);
        moreButton->setFlat(true);

        // 创建菜单
        auto menu = new QMenu(moreButton);
        menu->addAction("Share");
        menu->addAction("Rename");
        menu->addAction("Delete chat");
        menu->setVisible(false);
        // 将菜单关联到按钮
        moreButton->setMenu(menu);

        // 设置布局
        layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));  // 添加按钮
        layout->addWidget(moreButton);  // 添加按钮
        layout->addWidget(archButton);  // 添加按钮

        widget->setLayout(layout);
        widget->setObjectName("buttonsWidget");
        widget->setStyleSheet(""
                              "background: rgba(255, 255, 255, 128);"
                              "");


        widget->setVisible(false);
    }

private:

    QWidget* widget;

};


#endif // IHISTORYLIST_H
