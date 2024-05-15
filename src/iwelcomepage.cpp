#include "iwelcomepage.h"


IWelcomePage::IWelcomePage(QWidget *parent)
    : QWidget{parent}
    , ui(new Ui::IWelcomePage)
{
    ui->setupUi(this);
    ui->welcomeText1->setText("Tell me a random fun fact about the Roman Empire");
    ui->welcomeText3->setText("Create a personal webpage for me, all in a single file. Ask me 3 questions first on whatever you need to know.");
    ui->welcomeText2->setText("Write a short-and-sweet text message inviting my neighbor to a barbecue.");
    ui->welcomeText4->setText("Explain superconductors like I'm five years old.");
}
