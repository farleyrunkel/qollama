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
