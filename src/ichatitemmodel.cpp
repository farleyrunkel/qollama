#include "ichatitemmodel.h"

IChatItemModel::IChatItemModel(QObject *parent)
    : QStandardItemModel(parent)
{
}

QVariant IChatItemModel::data(const QModelIndex &index, int role) const
{
    if (role == ItemHeightRole) {
        return QStandardItemModel::data(index, Qt::SizeHintRole); // 返回项目的高度
    }
    return QStandardItemModel::data(index, role);
}

void IChatItemModel::setItemHeight(const QModelIndex &index, int height) const
{
    QStandardItem *item = itemFromIndex(index);
    if (item) {
        item->setData(height, ItemHeightRole); // 设置项目的高度
    }
}
