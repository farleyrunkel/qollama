#include "messagebox.h"
#include "ui_messagebox.h"

MessageBox::MessageBox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MessageBox)
{
    ui->setupUi(this);
}
MessageBox::MessageBox(QString text , QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MessageBox)
{
    ui->setupUi(this);
    ui->textLabel->setText(text);
}
MessageBox::MessageBox(QString user, QIcon icon, QString text, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MessageBox)
{
    ui->setupUi(this);
    ui->iconLabel->setPixmap(icon.pixmap(QSize(24, 24)));
    ui->userLabel->setText(user);
    ui->textLabel->setText(text);

    ui->iconLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->userLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->textLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    }


MessageBox::~MessageBox()
{
    delete ui;
}
