#ifndef IUSERPAGE_H
#define IUSERPAGE_H

#include <QWidget>
#include "ui_userpage.h"
#include <QMouseEvent>

namespace Ui {
class UserPage;
} // namespace Ui

class IUserPage : public QDialog
{
    Q_OBJECT
public:
    explicit IUserPage(QWidget *parent = nullptr);

signals:

private:

    Ui::UserPage ui;

};

#endif // IUSERPAGE_H
