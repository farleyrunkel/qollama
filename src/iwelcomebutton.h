#ifndef IWELCOMEBUTTON_H
#define IWELCOMEBUTTON_H

#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class IWelcomeButton : public QPushButton
{
public:
    using  QPushButton::QPushButton;

    IWelcomeButton(QWidget* parent = nullptr)
        : QPushButton(parent) {
        label = new QLabel("", this);
        label->setWordWrap(true);
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("background: transparent;"); // Make label background transparent

        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(label);
        setLayout(layout);
        this->setObjectName("IWelcomeButton");
        this->setIconSize(QSize(50, 50));
    }

    void setText(const QString &text){

        this->label->setText(text);
    }
private:

    QLabel* label ;
};

#endif // IWELCOMEBUTTON_H
