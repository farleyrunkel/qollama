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
};



#endif // ICHATITEMMODEL_H
