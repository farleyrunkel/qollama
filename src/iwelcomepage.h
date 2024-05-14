#ifndef IWELCOMEPAGE_H
#define IWELCOMEPAGE_H

#include <QWidget>
#include "ui_welcomepage.h"
#include <QMouseEvent>

namespace Ui {
class IWelcomePage;
}


class IWelcomePage : public QWidget
{
    Q_OBJECT
public:
    explicit IWelcomePage(QWidget *parent = nullptr);
signals:
    void send(QString);
private slots:

protected:
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            auto child = static_cast<QLabel* >( this->childAt(event->pos()));
            emit send(child->text());
        }
        QWidget::mousePressEvent(event);
    }

private:
    Ui::IWelcomePage *ui;

};
#endif // IWELCOMEPAGE_H
