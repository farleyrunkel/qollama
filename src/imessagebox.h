#ifndef IMESSAGEBOX_H
#define IMESSAGEBOX_H

#include <QWidget>
#include "ui_IMessageBox.h"

namespace Ui {
class IMessagebox;
}

class IMessagebox : public QWidget
{
    Q_OBJECT

public:
    explicit IMessagebox(QWidget *parent = nullptr);

    QSize sizeHint() const override {
        return ui->gridLayout->sizeHint();
    }

    ~IMessagebox();


    QString text() {return ui->chatLabel->text();}

    void setIcon(const QIcon & icon) {
        ui->iconLabel->setPixmap(icon.pixmap(ui->iconLabel->width(), ui->iconLabel->height()));
    }
    void setUser(QString text){ui->userLabel->setText(text);}

    void setChat(QString chat){
        ui->chatLabel->setText(chat);
        ui->chatLabel->adjustSize();
    }

private:
    Ui::IMessagebox *ui;
};

#endif // IMESSAGEBOX_H
