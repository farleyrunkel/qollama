#include "ilineedit.h"

ILineEdit::ILineEdit(QWidget *parent) : QLineEdit(parent) {
    // Set maximum height of the line edit
    setMaximumHeight(40);

    // Create left button and set properties
    m_leftButton = new QPushButton("", this);
    m_leftButton->setFixedSize(30, 30); // Set button size
    m_leftButton->setObjectName("circleButton");

    // Create right button and set properties
    m_rightButton = new QPushButton("", this);
    m_rightButton->setFixedSize(30, 30); // Set button size
    m_rightButton->setObjectName("circleButton");

    // Create horizontal layout
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->setContentsMargins(5, 0, 5, 0); // Set layout margins
    hLayout->setSpacing(5);                  // Set spacing between widgets

    // Add widgets to layout
    hLayout->addWidget(m_leftButton);
    hLayout->addStretch(1);
    hLayout->addWidget(m_rightButton);

    // Set the layout for the line edit
    setLayout(hLayout);
}

// Get left button
QPushButton *ILineEdit::leftButton() const { return m_leftButton; }

// Get right button
QPushButton *ILineEdit::rightButton() const { return m_rightButton; }
