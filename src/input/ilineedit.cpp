#include "ilineedit.h"

ILineEdit::ILineEdit(QWidget *parent) : QLineEdit(parent) {

    setMaximumHeight(40);

    m_leftButton = new QPushButton("", this);
    m_leftButton->setFixedSize(30, 30); // 设置按钮大小
    m_leftButton->setObjectName("circleButton");
    m_rightButton = new QPushButton("", this);
    m_rightButton->setFixedSize(30, 30); // 设置按钮大小
    m_rightButton->setObjectName("circleButton");
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->setContentsMargins(5, 0, 5, 0); // 设置布局边距为0
    hLayout->setSpacing(5);                  // 设置控件之间的间距

    hLayout->addWidget(m_leftButton);
    hLayout->addStretch(1);
    hLayout->addWidget(m_rightButton);

    setLayout(hLayout); // 设置主布局
}

QPushButton *ILineEdit::leftButton() const { return m_leftButton; }

QPushButton *ILineEdit::rightButton() const { return m_rightButton; }
