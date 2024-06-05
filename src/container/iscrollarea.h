#ifndef ISCROLLAREA_H
#define ISCROLLAREA_H

#include "qscrollbar.h"
#include <QScrollArea>

class IScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    IScrollArea(QWidget* parent = nullptr);


signals:
    void scrolledToValue(int);

protected:

    void scrollContentsBy(int dx, int dy) override
    {
        QScrollArea::scrollContentsBy(dx, dy);

        emit scrolledToValue(verticalScrollBar()->value());
    }

    void resizeEvent(QResizeEvent *event) override
    {
        QScrollArea::resizeEvent(event);
        if (widget()) {
            widget()->setFixedWidth(width());
        }
    }



};

#endif // ISCROLLAREA_H
