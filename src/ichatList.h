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

    void paintEvent(QPaintEvent *e) override {

        QListView::paintEvent(e);
        qDebug() << "    void paintEvent(QPaintEvent *e) override {";
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


    void appendText(QString text) {

        auto model = qobject_cast<QStandardItemModel*>(this->model());
        if (!model) {
            qDebug() << "Chat list model is null.";
            return;
        }

        QStandardItem *lastItem = nullptr;
        int rowCount = model->rowCount();
        if (rowCount > 0) {
            QModelIndex lastIndex = model->index(rowCount - 1, 0);
            lastItem = model->itemFromIndex(lastIndex);
        }

        if (!lastItem) {
            // 如果没有最后一行item，创建一个新的item并添加到模型中
            lastItem = new QStandardItem();
            model->appendRow(lastItem);
        }

        // 获取最后一个item的数据，并更新 message 字段
        QVariant itemData = lastItem->data(Qt::DisplayRole);
        QVariantMap chatData1 = itemData.toMap(); // 显式转换为 QVariantMap
        chatData1["message"] = chatData1["message"].toString() + " " + text;
        lastItem->setData(chatData1, Qt::DisplayRole);
        qDebug() << "appendText:" << text;
        // 发出数据变化信号，通知视图刷新
        QModelIndex topLeft = model->index(0, 0);
        QModelIndex bottomRight = model->index(rowCount - 1, 0);
        emit model->dataChanged(topLeft, bottomRight);

        repaint();
    }

public:
};





#endif // ICHATLIST_H
