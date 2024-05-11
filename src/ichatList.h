#ifndef ICHATLIST_H
#define ICHATLIST_H

#include <QListView>
#include <QStandardItemModel>
#include "ichatitemdelegate.h"
#include "ichatitemmodel.h"


class IChatList: public QListView
{

public:
    using QListView::QListView;

public:
    explicit IChatList(QWidget *parent = nullptr)
        : QListView(parent)
    {
        setModel(new IChatItemModel(this));
        setItemDelegate(new IChatItemDelegate(this));
    }

public:
    bool isNew() {return this->model()->rowCount() == 0;}

    void addItem(QIcon icon, QString user, QString text) {

        auto model = static_cast<QStandardItemModel*>(this->model());
        if (!model) {
            qDebug() << "Chat list model is null.";
            return;
        }

        // 添加聊天数据到模型中
        QVariantMap chatData1;
        chatData1["icon"] =icon;
        chatData1["username"] = user;
        chatData1["message"] = text;
        QStandardItem *item1 = new QStandardItem;
        item1->setData(chatData1, Qt::DisplayRole);
        model->appendRow(item1);
    }

public:
};





#endif // ICHATLIST_H
