#include "ihistorylist.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QMenu>
#include <QSpacerItem>
#include <QShowEvent>
#include <QAction>

IHistoryList::IHistoryList(QWidget *parent) : QListWidget(parent)
{
    setupUI();
    setItemDelegate(new IHistoryItemDelegate);
}

void IHistoryList::deleteChat(bool checked)
{
    delete this->takeItem(curr_index.row());

    emit itemDeleted(curr_index.row());
}

void IHistoryList::mouseMoveEvent(QMouseEvent *event)
{
    curr_index = this->indexAt(event->pos());

    if (curr_index.isValid()) {

        auto item_rect = this->visualRect(curr_index);

        for (int i = 1 ; i<= m_buttons.size(); i++) {
            setSubGeometry(item_rect, i);
            getSubButton(i)->setVisible(true);
        }
    }
    else {
        for (int i = 1 ; i<= m_buttons.size(); i++) {
            getSubButton(i)->setVisible(false);
        }
    }
}

void IHistoryList::setupUI()
{
    setIconSize(QSize(100, 100)); // 设置item中的图标大小
    setObjectName("historyList");
    setUniformItemSizes(true);

    auto deleButton = addButton(":/icon/delete.svg", "Delete");
    auto moreButton = addButton(":/icon/more-horiz.svg", "More");

    QMenu *menu = new QMenu(moreButton);

    auto shareAction =  menu->addAction("Share");
    auto renameAction =  menu->addAction("Rename");
    auto deleteAction =  menu->addAction("Delete chat");
    moreButton->setMenu(menu);

    connect(deleButton, &QPushButton::clicked, this, &IHistoryList::deleteChat);
    connect(deleteAction, &QAction::triggered, this, &IHistoryList::deleteChat);
}

void IHistoryList::setSubGeometry(const QRect &rect, int i)
{
    if (i <= 0) return;
    int margin = rect.height() * 0.25;
    int h = rect.height() - (margin * 2);
    int w = h;
    int y = rect.y() + margin;
    int x = rect.x() + rect.width() - i * ( w  + margin);

    getSubButton(i)->setGeometry(x, y, w, h);
}

QPushButton* IHistoryList::addButton(const QString &icon, const QString &tooltip)
{
    auto button = new QPushButton(QIcon(icon), "", this);
    button->setFlat(true);
    button->setFocusPolicy(Qt::NoFocus);
    button->setFixedSize(QSize(16, 16));
    button->setToolTip(tooltip);
    button->setVisible(false);

    m_buttons.push_back(button);
    return button;
}

QPushButton* IHistoryList::getSubButton(int i)
{
    if (i <= 0) return nullptr;
    return m_buttons[i-1];
}
