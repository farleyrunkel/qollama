#ifndef IWELCOMEPAGE_H
#define IWELCOMEPAGE_H

#include <QWidget>
#include "ui_welcomepage.h"

namespace Ui {
class IWelcomePage;
}


class IWelcomePage : public QWidget
{
    Q_OBJECT
public:
    explicit IWelcomePage(QWidget *parent = nullptr);
signals:

private slots:
    void on_pushButton_clicked();

private:
    Ui::IWelcomePage *ui;

};
#endif // IWELCOMEPAGE_H
