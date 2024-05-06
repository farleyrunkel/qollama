#ifndef IHISTORYITEM_H
#define IHISTORYITEM_H

#include <QWidget>
#include <QListWidgetItem >
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QObject>
#include "ioverlaybutton.h"

class IHistoryItem: public QListWidgetItem {

public:

    explicit IHistoryItem(QListWidget *listview = nullptr, int type = Type) : QListWidgetItem(listview, type) {}
    explicit IHistoryItem(const QIcon &icon, const QString &text,
                          QListWidget *listview = nullptr, int type = Type) : QListWidgetItem(icon, text, listview, type) {}
    IHistoryItem(const QListWidgetItem &other);

    explicit IHistoryItem(const QString &text, QListWidget *listview = nullptr, int type = Type) : QListWidgetItem(text, listview, type)
    {
      //   // 创建按钮
      //   QPushButton *moreButton = new QPushButton(QIcon("://icon/more-horiz.svg"), "");
      //   moreButton->setFixedSize(QSize(16, 16));
      //   QPushButton *archButton = new QPushButton(QIcon("://icon/archive-book.svg"), "");
      //   archButton->setFixedSize(QSize(16, 16));
      //   archButton->setFlat(true);
      //   moreButton->setFlat(true);
      //   // 设置布局
      //   QHBoxLayout *layout = new QHBoxLayout;
      //   layout->addItem(new QSpacerItem(listview->width(), 0, QSizePolicy::Expanding, QSizePolicy::Expanding));  // 添加按钮
      //   layout->addWidget(moreButton);  // 添加按钮
      //   layout->addWidget(archButton);  // 添加按钮

      // //  layout->setContentsMargins(0, 6, 0, 6);  // 设置边距为0
      //   QWidget *widget = new QWidget(listview);
      //   widget->setLayout(layout);
      //   widget->setObjectName("historyitem");


          auto widget = new IHistoryButton(listview);
          widget->setFixedHeight(32);

        setSizeHint(widget->size());  // 设置Item的大小
        // 设置Item的Widget

        this->setFlags(this->flags() | Qt::ItemIsSelectable | Qt::ItemIsEnabled);

        listview->addItem(this);
        listview->setItemWidget(this, widget);



    }

    // void resizeEvent(QResizeEvent * event) {

    // }

public slots:
    void onButtonClick() {
        qDebug() << "Button clicked on item: " << text();
    }
};


#endif // IHISTORYITEM_H
