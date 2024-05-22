#include "itestwidget.h"
#include "waitingspinnerwidget.h"

ITestWidget::ITestWidget(QWidget *parent)
    : QDialog(parent)
{

    setAutoFillBackground(true);
    setFixedSize(QSize(500, 500));

    auto spinner = new WaitingSpinnerWidget(this);

    spinner->setRoundness(100.0);
    spinner->setMinimumTrailOpacity(15.0);
    spinner->setTrailFadePercentage(10.0);
    spinner->setNumberOfLines(10);
    spinner->setLineLength(10);
    spinner->setLineWidth(10);
    spinner->setInnerRadius(0);
    spinner->setRevolutionsPerSecond(1);
    spinner->setColor(QColor(84, 210, 99));

    spinner->start(); // gets the show on the road!
}
