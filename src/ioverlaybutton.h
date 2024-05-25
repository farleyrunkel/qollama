#ifndef IOVERLAYBUTTON_H
#define IOVERLAYBUTTON_H

#include <QPushButton>
#include <QResizeEvent>
#include <QDebug>
#include <QPainter>

class INewChatButton : public QPushButton
{
    Q_OBJECT

public:
    INewChatButton(QWidget* parent)
        : QPushButton(parent)
    {
        setIcon(QIcon("://icon/qollama.png"));
        setStyleSheet(R"(
            INewChatButton {
                border: 1px hidden gray;
                border-radius: 6px;
                padding-left: 10px; /* 设置左边距 */
                text-align: left; /* 设置文本左对齐 */
            }
            INewChatButton:hover {
                background-color: #ececec;
                color: black;
            }
            INewChatButton:pressed {
                background-color: #ececec;
                border-style: hidden;
            }
        )");

        addSubButton(QIcon("://icon/create-new.svg"));
        getSubButton(1)->setToolTip("New chat");
    }

public:

    void resizeEvent(QResizeEvent* event) override {
        for (int i = 1 ; i<= m_buttons.size(); i++) {
            setSubGeometry(i);
        }
        update();
    }

public:

    void addSubButton(const QIcon& icon, const QString &text = "") {
        auto sub = new QPushButton(icon, text, this->parentWidget());
        sub->setFlat(true);
        sub->setFocusPolicy(Qt::NoFocus);

        m_buttons.push_back(sub);
        setSubGeometry(m_buttons.size());
    }

    QPushButton* getSubButton(int i) {
        if (i <= 0) return nullptr;
        return m_buttons[i-1];
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

private:
    std::vector<QPushButton*> m_buttons;
};


#endif // IOVERLAYBUTTON_H
