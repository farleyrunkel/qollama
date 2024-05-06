#ifndef IOVERLAYBUTTON_H
#define IOVERLAYBUTTON_H

#include <QPushButton>
#include <QResizeEvent>
#include <QDebug>
#include <QPainter>

class IOverlayButton : public QPushButton
{
    Q_OBJECT
public:
    IOverlayButton(QWidget* parent = nullptr) : QPushButton(parent) {}
    IOverlayButton(const QIcon& icon, const QString &text, QWidget *parent = nullptr)
        : QPushButton(icon, text, parent) { }
public:
    void resizeEvent(QResizeEvent* event) override {

        for (int i = 1 ; i<= mSubButtons.size(); i++) {
            setSubGeometry(i);
        }
        update();
    }

public:

    void addSubButton(const QIcon& icon, const QString &text = "") {
        auto sub = new QPushButton(icon, text, this->parentWidget());
        sub->setFlat(true);
        sub->setToolTip("New chat");
        sub->setFocusPolicy(Qt::NoFocus);

        mSubButtons.push_back(sub);
        setSubGeometry(mSubButtons.size());
    }

    QPushButton* getSubButton(int i) {
        if (i <= 0) return nullptr;
        return mSubButtons[i-1];
    }

    void setSubGeometry(int i) {
        if (i <= 0) return ;
        int margin = this->height() * 0.25;
        int h = this->height() - (margin * 2);
        int w = h;
        int y = this->y() + margin;
        int x = this->x() + this->width() - i * ( w  + margin);

        getSubButton(i)->setGeometry(x, y, w, h);
    }

    // void paintEvent(QPaintEvent *event) override
    // {
    //     Q_UNUSED(event);

    //     QPushButton::paintEvent(event);

    //     QPainter painter(this);

    //     // 指定圆形的中心点和半径
    //     QPoint p1(this->x(), this->y());
    //     int radius = 1;
    //     QPoint p2(getSubButton(1)->x(), getSubButton(1)->y());
    //     // 绘制圆形
    //     painter.setBrush(Qt::red); // 设置画刷颜色为红色
    //    painter.drawEllipse(p1, radius, radius);
    //     painter.drawEllipse(p2, radius, radius);
    // }

private:

    std::vector<QPushButton*> mSubButtons;
};



class INewChatButton : public IOverlayButton
{
    Q_OBJECT
public:
    INewChatButton(QWidget* parent):
        IOverlayButton(parent)
    {
        addSubButton(QIcon("://icon/create-new.svg"));
    };
};

class IHistoryButton : public IOverlayButton
{
    Q_OBJECT
public:
    IHistoryButton(QWidget* parent):
        IOverlayButton(parent)
    {
        addSubButton(QIcon("://icon/archive-book.svg"));
        addSubButton(QIcon("://icon/more-horiz.svg"));

        getSubButton(1)->setToolTip("Archive");
        getSubButton(2)->setToolTip("More");
    };
};



#endif // IOVERLAYBUTTON_H
