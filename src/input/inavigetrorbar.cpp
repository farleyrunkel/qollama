#include "INavigetrorBar.h"
#include <QGridLayout>
#include <QDebug>

INavigetrorBar::INavigetrorBar(QWidget *parent)
    : QWidget(parent), m_currentUnderlineLabel(nullptr)
{
    m_buttonLayout = new QGridLayout(this);
    m_buttonLayout->setContentsMargins(0, 10, 0, 0);

    qDebug() << "INavigetrorBar created and UI setup completed";
}

void INavigetrorBar::addButton(const QString& text) {
    qDebug() << "Adding button with text:" << text;

    auto button = new QPushButton(text, this);
    button->setObjectName("navigatorButton");

    auto underlineLabel = new QLabel(this);
    underlineLabel->setObjectName("underlineLabel");
    underlineLabel->setFixedHeight(2);
    underlineLabel->setStyleSheet("background-color: #54D263;");
    underlineLabel->hide(); // Initially hide the underline label

    int colCount = m_buttonLayout->columnCount();
    m_buttonLayout->addWidget(button, 0, colCount);
    m_buttonLayout->addWidget(underlineLabel, 1, colCount);

    qDebug() << "QPushButton and QLabel created and added to QGridLayout";

    m_underlineLabelMap.insert(text, underlineLabel);

    connect(button, &QPushButton::clicked, this, [this, button, underlineLabel]() {
        qDebug() << "Button clicked with text:" << button->text();
        showUnderline(underlineLabel);
        emit buttonClicked(button);
    });
}

void INavigetrorBar::showUnderline(QLabel* underlineLabel) {
    qDebug() << "Showing underline";

    if (m_currentUnderlineLabel == underlineLabel) {
        qDebug() << "The underline is already shown for this label. No action taken.";
        return;
    }

    if (m_currentUnderlineLabel) {
        m_currentUnderlineLabel->hide(); // Hide the currently shown underline label
    }

    m_currentUnderlineLabel = underlineLabel;
    m_currentUnderlineLabel->show(); // Show the underline label for the clicked button

    qDebug() << "Underline shown for label " << m_currentUnderlineLabel->objectName();
}

QLabel* INavigetrorBar::getUnderlineLabel(const QString& text) const {
    return m_underlineLabelMap.value(text, nullptr);
}
