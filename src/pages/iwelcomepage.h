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

protected:
    void mousePressEvent(QMouseEvent *event) override;


private:
    Ui::IWelcomePage *ui;

};
#endif // IWELCOMEPAGE_H
