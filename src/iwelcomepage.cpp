#include "iwelcomepage.h"


IWelcomePage::IWelcomePage(QWidget *parent)
    : QWidget{parent}
    , ui(new Ui::IWelcomePage)
{
    ui->setupUi(this);
}

void IWelcomePage::on_pushButton_clicked()
{
    IWelcomePage::close();
}

