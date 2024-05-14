#include "iwelcomepage.h"


IWelcomePage::IWelcomePage(QWidget *parent)
    : QWidget{parent}
    , ui(new Ui::IWelcomePage)
{
    ui->setupUi(this);
    ui->welcomeLabel1->setText("Tell me a random fun fact about the Roman Empire");
    ui->welcomeLabel2->setText("Create a personal webpage for me, all in a single file. Ask me 3 questions first on whatever you need to know.");
    ui->welcomeLabel3->setText("Write a short-and-sweet text message inviting my neighbor to a barbecue.");
    ui->welcomeLabel4->setText("Explain superconductors like I'm five years old.");
}
