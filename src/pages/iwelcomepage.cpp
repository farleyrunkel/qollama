#include "iwelcomepage.h"

IWelcomePage::IWelcomePage(QWidget *parent)
    : QWidget{parent}
    , ui(new Ui::IWelcomePage)
{
    ui->setupUi(this);
    ui->welcomeText1->setText("Why the sky is blue?");
    ui->welcomeText3->setText("Create a personal webpage for me, all in a single file. Ask me 3 questions first on whatever you need to know.");
    ui->welcomeText2->setText("Write a short-and-sweet text message inviting my neighbor to a barbecue.");
    ui->welcomeText4->setText("Tell me a random fun fact about the Roman Empire");

    // Create a QPalette object and set the background color to black
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, Qt::white);
    this->setPalette(pal);
    // Ensure the widget uses the palette to fill the background
    this->setAutoFillBackground(true);

    connect(ui->welInputLine, &QLineEdit::returnPressed, [&]()  {emit send(ui->welInputLine->text());});
    connect(ui->welInputButton, &QPushButton::pressed, [&]()  {emit send(ui->welInputLine->text());});
}

void IWelcomePage::mousePressEvent(QMouseEvent *event) {
    QWidget::mousePressEvent(event);
    if (event->button() == Qt::LeftButton) {
        auto child = this->childAt(event->pos());
        if (child) {
            QString name = QString("welcomeText") + child->objectName().back();
            QLabel* label = this->findChild<QLabel*>(name);
            if (label) {
                emit send(label->text());
            } else {
                qDebug() << "No matching QLabel found";
            }
        } else {
            qDebug() << "No child widget found at" << event->pos();
        }
    }
}
