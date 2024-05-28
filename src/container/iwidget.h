#ifndef IWIDGET_H
#define IWIDGET_H

#include <QWidget>

class IWidget : public QWidget
{
    Q_OBJECT
public:
    IWidget(QWidget *parent = nullptr);

signals:
    void shown(bool);

protected:
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;
};

#endif // IWIDGET_H
