#include "ihistorylist.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QMenu>
#include <QSpacerItem>
#include <QShowEvent>

IHistoryList::IHistoryList(QWidget *parent) : QListWidget(parent) {
}

void IHistoryList::showEvent(QShowEvent *event) {
    QListWidget::showEvent(event);
    initButtonsWidget();
    setIconSize(QSize(100, 100)); // 设置item中的图标大小
    setItemDelegate(new CustomItemDelegate);
    setObjectName("historyList");
    setUniformItemSizes(true);
}

void IHistoryList::mouseMoveEvent(QMouseEvent *event) {
    QListWidget::mouseMoveEvent(event);
    auto index = this->indexAt(event->pos());

    if (index.isValid()) {
        auto item_rect = this->visualRect(index);

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

void IHistoryList::initButtonsWidget() {

    addSubButton(":/icon/archive-book.svg", "Archive");
    addSubButton(":/icon/more-horiz.svg", "More");

    auto moreButton = getSubButton(2);
    QMenu *menu = new QMenu(moreButton);
    menu->addAction("Share");
    menu->addAction("Rename");
    menu->addAction("Delete chat");
    moreButton->setMenu(menu);
}

void IHistoryList::setSubGeometry(const QRect &rect, int i) {
    if (i <= 0) return ;
    int margin = rect.height() * 0.25;
    int h = rect.height() - (margin * 2);
    int w = h;
    int y = rect.y() + margin;
    int x = rect.x() + rect.width() - i * ( w  + margin);

    getSubButton(i)->setGeometry(x, y, w, h);
}

void IHistoryList::addSubButton(const QString &icon, const QString &tooltip) {
    auto button = new QPushButton(QIcon(icon), "", this);
    button->setFlat(true);
    button->setFocusPolicy(Qt::NoFocus);
    button->setFixedSize(QSize(16, 16));
    button->setToolTip(tooltip);
    button->setVisible(false);

    m_buttons.push_back(button);
}

QPushButton *IHistoryList::getSubButton(int i) {
    if (i <= 0) return nullptr;
    return m_buttons[i-1];
}
