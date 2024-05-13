#include "ichatList.h"
#include "ichatitemdelegate.h"
#include "ichatitemmodel.h"

IChatList::IChatList(QWidget *parent)
    : QListView(parent)
{
    setModel(new IChatItemModel(this));
    setItemDelegate(new IChatItemDelegate(this));
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
}

bool IChatList::isNew() const {
    return model() ? model()->rowCount() == 0 : false;
}

void IChatList::addItem(const QIcon &icon, const QString &user, const QString &text) {
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(this->model());
    if (!model) {
        qDebug() << "Chat list model is null.";
        return;
    }

    // Add chat data to the model
    QVariantMap chatData;
    chatData["icon"] = icon;
    chatData["username"] = user;
    chatData["message"] = text;
    QStandardItem* item = new QStandardItem;
    item->setData(chatData, Qt::DisplayRole);
    model->appendRow(item);
}

void IChatList::appendText(const QString &text) {
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(this->model());
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

void IChatList::paintEvent(QPaintEvent *event) {
    QListView::paintEvent(event);
    qDebug() << "void paintEvent(QPaintEvent *event)";
}
