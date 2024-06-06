#include "iscrollarea.h"
#include "qscrollbar.h"
#include <QVBoxLayout>

IScrollArea::IScrollArea(QWidget *parent) : QScrollArea(parent) {}

void IScrollArea::scrollContentsBy(int dx, int dy) {
    QScrollArea::scrollContentsBy(dx, dy);

    emit scrolledToValue(verticalScrollBar()->value());
}

void IScrollArea::resizeEvent(QResizeEvent *event) {
    QScrollArea::resizeEvent(event);
    if (widget()) {
        widget()->setFixedWidth(width());
    }
}
