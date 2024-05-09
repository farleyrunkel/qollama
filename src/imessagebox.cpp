#include "imessagebox.h"
#include "ui_imessagebox.h"

IMessagebox::IMessagebox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::IMessagebox)
{
    ui->setupUi(this);

    ui->chatLabel->setWordWrap(true);
    ui->chatLabel->setAlignment(Qt::AlignTop);
};


IMessagebox::~IMessagebox()
{
    delete ui;
}
