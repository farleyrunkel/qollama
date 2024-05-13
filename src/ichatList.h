#ifndef ICHATLIST_H
#define ICHATLIST_H

#include <QListView>
#include <QStandardItemModel>

class IChatList: public QListView
{
    Q_OBJECT

public:
    explicit IChatList(QWidget *parent = nullptr);

    bool isNew() const;

    void addItem(const QIcon& icon, const QString& user, const QString& text);

    void appendText(const QString& text);

protected:
    void paintEvent(QPaintEvent* event) override;
};

#endif // ICHATLIST_H
