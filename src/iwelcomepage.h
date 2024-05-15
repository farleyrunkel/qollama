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
            qDebug() << "Left button pressed";

            auto child = this->childAt(event->pos());

            if (child) {
                qDebug() << "Child widget found at" << event->pos();
                qDebug() << "Looking at QFrame with name:" << child->objectName();

                QString name = QString("welcomeText") + child->objectName().back();
                qDebug() << "Looking for QLabel with name:" << name;

                QLabel* label = this->findChild<QLabel*>(name);
                if (label) {
                    qDebug() << "Found QLabel with text:" << label->text();
                    emit send(label->text());
                } else {
                    qDebug() << "No matching QLabel found";
                }
            } else {
                qDebug() << "No child widget found at" << event->pos();
            }
        }
        QWidget::mousePressEvent(event);
    }


private:
    Ui::IWelcomePage *ui;

};
#endif // IWELCOMEPAGE_H
