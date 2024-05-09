#ifndef IHISTORYLIST_H
#define IHISTORYLIST_H

#include <QWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMenu>
#include <QSpacerItem>
#include <QShowEvent>
#include <QStyledItemDelegate>

class CustomItemDelegate : public QStyledItemDelegate {
public:
    CustomItemDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override
    {
        QSize size = QStyledItemDelegate::sizeHint(option, index);
        size.setHeight(32);
        return size;
    }

    // void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
    //     QStyledItemDelegate::paint(painter, option, index);

    //     QRect rect = option.rect;

    //     QRect buttonRect1 = QRect(rect.right() - 60, rect.top() + 2, 30, 30);

    //     painter->setBrush(Qt::red);
    //     painter->drawRect(buttonRect1);

    //     QRect buttonRect2 = QRect(rect.right() - 30, rect.top() + 2, 30, 30);

    //     painter->setBrush(Qt::blue);
    //     painter->drawRect(buttonRect2);
    // }
};


class IHistoryList : public QListWidget {
public:
    IHistoryList(QWidget *parent = nullptr) : QListWidget(parent) {}

protected:
    void showEvent(QShowEvent *event) override {
        QListWidget::showEvent(event);
        initButtonsWidget();
        setIconSize(QSize(100, 100)); // 设置item中的图标大小
        setItemDelegate(new CustomItemDelegate);
        setObjectName("historyList");
        setUniformItemSizes(true);
    }
    void mouseMoveEvent(QMouseEvent* event) override {
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

private:
    void initButtonsWidget() {

        addSubButton(":/icon/archive-book.svg", "Archive");
        addSubButton(":/icon/more-horiz.svg", "More");

        auto moreButton = getSubButton(2);
        QMenu *menu = new QMenu(moreButton);
        menu->addAction("Share");
        menu->addAction("Rename");
        menu->addAction("Delete chat");
        moreButton->setMenu(menu);
    }

    void setSubGeometry(const QRect& rect, int i) {
        if (i <= 0) return ;
        int margin = rect.height() * 0.25;
        int h = rect.height() - (margin * 2);
        int w = h;
        int y = rect.y() + margin;
        int x = rect.x() + rect.width() - i * ( w  + margin);

        getSubButton(i)->setGeometry(x, y, w, h);
    }

    QPushButton* getSubButton(int i) {
        if (i <= 0) return nullptr;
        return m_buttons[i-1];
    }

    void addSubButton(const QString& icon, const QString &tooltip = "") {
        auto button = new QPushButton(QIcon(icon), "", this);
        button->setFlat(true);
        button->setFocusPolicy(Qt::NoFocus);
        button->setFixedSize(QSize(16, 16));
        button->setToolTip(tooltip);
        button->setVisible(false);

        m_buttons.push_back(button);
    }

private:
    std::vector<QPushButton*> m_buttons;

};

#endif // IHISTORYLIST_H
