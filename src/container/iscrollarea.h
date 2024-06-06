#ifndef ISCROLLAREA_H
#define ISCROLLAREA_H

#include <QScrollArea>

class IScrollArea : public QScrollArea {
    Q_OBJECT
public:
    IScrollArea(QWidget *parent = nullptr);

signals:
    void scrolledToValue(int);

protected:
    void scrollContentsBy(int dx, int dy) override;

    void resizeEvent(QResizeEvent *event) override;
};

#endif // ISCROLLAREA_H
