#ifndef ICHATLIST_H
#define ICHATLIST_H

#include <QListView>
#include <QStandardItemModel>
#include "chatitemdelegate.h"


class IChatList: public QListView
{

public:
    using QListView::QListView;

public:
    explicit IChatList(QWidget *parent = nullptr)
        : QListView(parent)
    {
        setModel(new QStandardItemModel(this));
        setItemDelegate(new ChatItemDelegate(this));
    }


public:
    bool isNew() {return this->model()->rowCount() == 0;}

public:
};



#endif // ICHATLIST_H
