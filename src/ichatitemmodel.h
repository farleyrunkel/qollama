#ifndef ICHATITEMMODEL_H
#define ICHATITEMMODEL_H

#include <QStandardItemModel>

class IChatItemModel : public QStandardItemModel
{
    Q_OBJECT
public:
    enum CustomRoles {
        ItemHeightRole = Qt::UserRole + 1, // 自定义角色，用于保存项目的高度
    };

    explicit IChatItemModel(QObject *parent = nullptr);
    QVariant data(const QModelIndex &index, int role) const override;

    void appendText(const QString &text) {
        QStandardItemModel* model = this;
        if (!model) {
            qDebug() << "Chat list model is null.";
            return;
        }

        QModelIndex lastIndex = model->index(model->rowCount() - 1, 0);
        QStandardItem* lastItem = model->itemFromIndex(lastIndex);
        if (!lastItem) {
            lastItem = new QStandardItem();
            model->appendRow(lastItem);
        }

        // Update message field of the last item
        QVariant itemData = lastItem->data(Qt::DisplayRole);
        QVariantMap chatData = itemData.toMap();
        chatData["message"] = chatData["message"].toString() + text;
        lastItem->setData(chatData, Qt::DisplayRole);

        qDebug() << "appendText:" << text;

        // Emit dataChanged signal to refresh the view
        emit model->dataChanged(lastIndex, lastIndex);
    }
};



#endif // ICHATITEMMODEL_H
