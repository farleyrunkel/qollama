#ifndef IWIDGET_H
#define IWIDGET_H

#include <QMetaMethod>
#include <QMetaObject>
#include <QWidget>

class IWidget : public QWidget {
    Q_OBJECT
public:
    IWidget(QWidget *parent = nullptr);

signals:
    void hidden(bool);

protected:
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;
};

#endif // IWIDGET_H
