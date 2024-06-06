#include "ioverlaybutton.h"

IOverlayButton::IOverlayButton(QWidget *parent) : QPushButton(parent) {
    m_mainLayout = new QHBoxLayout;
    setLayout(m_mainLayout);

    m_mainLayout->setAlignment(Qt::AlignRight);
    setMouseTracking(true); // Enable mouse tracking to detect hover
}

void IOverlayButton::addSubButton(QIcon icon) {
    QPushButton* button = new ISubButton;
    button->setIcon(icon);
    m_mainLayout->addWidget(button);
    button->hide(); // Initially hide the button
    m_subButtons.append(button); // Add the button to the list of sub-buttons
}

QList<QPushButton *> IOverlayButton::getSubButtons() const {
    return m_subButtons;
}

QPushButton *IOverlayButton::getSubButton(int index) const {
    if (index >= 0 && index < m_subButtons.size()) {
        return m_subButtons[index];
    }
    return nullptr; // Return nullptr if index is out of range
}

bool IOverlayButton::event(QEvent *e) {
    if (e->type() == QEvent::Enter) {
        showSubButtons(); // Show sub-buttons on hover enter
    } else if (e->type() == QEvent::Leave) {
        hideSubButtons(); // Hide sub-buttons on hover leave
    }
    return QPushButton::event(e);
}

void IOverlayButton::showSubButtons() {
    for (auto button : m_subButtons) {
        button->show();
        button->setDisabled(true);
    }
}

void IOverlayButton::hideSubButtons() {
    for (auto button : m_subButtons) {
        button->hide();
    }
}
