#ifndef IHISTORYMODEL_H
#define IHISTORYMODEL_H

#include <QAbstractItemModel>
#include <QStringList>
#include <QStandardItemModel>

class IHistoryModel : public QAbstractItemModel
{
public:
    explicit IHistoryModel(QObject *parent = nullptr) {

        m_data << "Item 1" << "Item 2" << "Item 3" << "Item 4" << "Item 5";
    }

public:

    int rowCount(const QModelIndex &parent = QModelIndex())const override {
        if (parent.isValid())
            return 0;
        return m_data.size();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) {

        if (!index.isValid())
            return QVariant();

        if (role == Qt::DisplayRole || role == Qt::EditRole)
            return m_data.at(index.row());

        return QVariant();
    }

private:
    QStringList  m_data;
};


#endif // IHISTORYMODEL_H
