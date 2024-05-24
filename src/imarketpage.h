#ifndef IMARKETPAGE_H
#define IMARKETPAGE_H

#include <QScrollArea>
#include <QHBoxLayout>
#include <QCalendarWidget>
#include <QSizePolicy>

class IMarketPage : public QScrollArea
{
    Q_OBJECT
public:
    IMarketPage(QWidget* parent = nullptr) : QScrollArea(parent) {
        container = new QWidget(this);
        mainLayout = new QHBoxLayout(container);

        setMinimumHeight(400);
        setMinimumWidth(600);

        // Set the size policy to ensure the container can expand
        container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        // Set the container widget to QScrollArea
        setWidget(container);
        setWidgetResizable(true);

        mainLayout->addWidget(new QCalendarWidget(container));
    };

private:
    QHBoxLayout* mainLayout;
    QWidget* container;
};

#endif // IMARKETPAGE_H
