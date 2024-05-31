#ifndef IWELCOMEPAGE_H
#define IWELCOMEPAGE_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QSpacerItem>
#include <QMouseEvent>
#include "ilineedit.h"
#include "ivpushcard.h"

class IWelcomePage : public QWidget
{
    Q_OBJECT

public:
    explicit IWelcomePage(QWidget *parent = nullptr);

signals:

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    void setupUi(QWidget *parent);

    void retranslateUi();

    void addPushCardWidgets();

private:
    QGridLayout *m_mainLayout;
    QLabel* m_welcomeLogo;
    ILineEdit *m_inputLine;

    IVPushCard *card1;
    IVPushCard *card2;
    IVPushCard *card3;
    IVPushCard *card4;
};

#endif // IWELCOMEPAGE_H
