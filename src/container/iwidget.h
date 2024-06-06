#ifndef IWIDGET_H
#define IWIDGET_H

#include <QWidget>
#include <QMetaObject>
#include <QMetaMethod>

// 定义宏
#define INJECT_SHOW_HIDE_EVENTS(className) \
protected: \
    void showEvent(QShowEvent *event) override { \
        QWidget::showEvent(event); \
        QMetaObject::invokeMethod(this, "shown", Q_ARG(bool, true)); \
} \
    void hideEvent(QHideEvent *event) override { \
        QWidget::hideEvent(event); \
        QMetaObject::invokeMethod(this, "shown", Q_ARG(bool, false)); \
} \
    signals: \
    void shown(bool);


class IWidget : public QWidget
{
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
