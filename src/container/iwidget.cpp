#include "iwidget.h"

IWidget::IWidget(QWidget *parent) {
    setAttribute(Qt::WA_StyledBackground, true);
}

void IWidget::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    emit shown(true);
}

void IWidget::hideEvent(QHideEvent *event) {
    QWidget::hideEvent(event);
    emit shown(false);
}
