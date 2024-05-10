#ifndef ICHATLIST_H
#define ICHATLIST_H

#include <QListView>


class IChatList: public QListView
{

public:
    using QListView::QListView;

public:
    bool isNew() {return true;}



};





#endif // ICHATLIST_H
