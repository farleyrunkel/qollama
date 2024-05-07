#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QWidget>

namespace Ui {
class MessageBox;
}

class MessageBox : public QWidget
{
    Q_OBJECT

public:
    explicit MessageBox(QWidget *parent = nullptr);
    explicit MessageBox(QString text, QWidget *parent = nullptr);

    explicit MessageBox(QString user, QIcon icon, QString text, QWidget *parent = nullptr);
    ~MessageBox();

private:
    Ui::MessageBox *ui;
};

#endif // MESSAGEBOX_H
