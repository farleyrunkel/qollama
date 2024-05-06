#ifndef IHISTORYLIST_H
#define IHISTORYLIST_H

#include <QWidget>
#include <QListWidgetItem >
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QObject>
#include "ioverlaybutton.h"

class IHistoryList: public QListWidget
{

public:

    using QListWidget::QListWidget;

public:
    // todo: fix button position not align.
    void addItem(const QString &label)  {
        auto item = new QListWidgetItem(label);

        QHBoxLayout *layout = new QHBoxLayout;

        QPushButton *moreButton = new QPushButton(QIcon("://icon/more-horiz.svg"), "");
        moreButton->setFixedSize(QSize(16, 16));
        QPushButton *archButton = new QPushButton(QIcon("://icon/archive-book.svg"), "");
        archButton->setFixedSize(QSize(16, 16));

        archButton->setFlat(true);
        moreButton->setFlat(true);

        // 设置布局
        layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));  // 添加按钮
        layout->addWidget(moreButton);  // 添加按钮
        layout->addWidget(archButton);  // 添加按钮

        QWidget *widget = new QWidget(this);

        widget->setLayout(layout);
        widget->setObjectName("historyitem");

        item->setSizeHint(widget->sizeHint());

        QListWidget::addItem(item);
        QListWidget::setItemWidget(item, widget);
    }

public:

    // void resizeEvent(QResizeEvent * event) {
    //     QListWidget::resizeEvent(event);

    //     // for (int i = 1; i < this->count(); i++) {
    //     //     this->itemWidget(item(2))->update();
    //     // }
    // }

};


#endif // IHISTORYLIST_H
