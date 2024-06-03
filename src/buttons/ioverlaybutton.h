#ifndef IOVERLAYBUTTON_H
#define IOVERLAYBUTTON_H

#include <QPushButton>
#include <QHBoxLayout>

class IOverlayButton : public QPushButton
{
    Q_OBJECT

public:
    IOverlayButton(QWidget* parent)
        : QPushButton(parent)
    {
        setIcon(QIcon("://icon/qollama.png"));

        mainLayout = new QHBoxLayout;
        setLayout(mainLayout);

        mainLayout->setAlignment(Qt::AlignRight);

        auto button = new QPushButton;
        button->setIcon(QIcon("://icon/create-new.svg"));
        mainLayout->addWidget(button);
        button->hide();
    }

private:
    QHBoxLayout* mainLayout;
};


#endif // IOVERLAYBUTTON_H
