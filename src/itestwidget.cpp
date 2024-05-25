#include "itestwidget.h"
#include "waitingspinnerwidget.h"
#include "igallerywidget.h"
#include "imarketpage.h"

ITestWidget::ITestWidget(QWidget *parent)
    : QDialog(parent)
{

    setAutoFillBackground(true);
    setFixedSize(QSize(500, 500));
    auto mainLayout = new QHBoxLayout(this);
    setLayout(mainLayout);

    auto widget = new IGalleryList(this);
    mainLayout->addWidget(widget);
}
