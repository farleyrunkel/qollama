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

        // 在窗口类的构造函数或者初始化函数中连接信号和槽
        connect(this->model(), &IChatItemModel::dataChanged, this, &IChatList::onDataChanged);

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
        qDebug() << "appendText:" << text;
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
        this->update();
    }

    // onDataChanged 槽函数实现
    void onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                                  const QList<int> &roles = QList<int>()){
        Q_UNUSED(topLeft);
        Q_UNUSED(bottomRight);
        Q_UNUSED(roles);

        // 执行刷新操作
        update(); // 或者调用你需要的刷新操作
    }
public:
};





#endif // ICHATLIST_H
