#include "imessagebox.h"
#include "ui_imessagebox.h"

IMessagebox::IMessagebox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::IMessagebox)
{
    ui->setupUi(this);

    ui->iconLabel->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
    ui->userLabel->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);

    ui->chatLabel->setWordWrap(true);
    ui->chatLabel->setAlignment(Qt::AlignTop);
    ui->chatLabel->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
};


IMessagebox::~IMessagebox()
{
    delete ui;
}
