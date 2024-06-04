#ifndef IWELCOMEPAGE_H
#define IWELCOMEPAGE_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QSpacerItem>
#include <QMouseEvent>
#include "ilineedit.h"
#include "ivpushcard.h"
#include <Qmenu>
#include "iwidget.h"

class IWelcomePage : public IWidget
{
    Q_OBJECT

public:
    explicit IWelcomePage(QWidget *parent = nullptr);

signals:

private:
    void setupLayout();

    void retranslateUi();

    void setupPushCards();
    void setupLineEdit();
    void setupModelLabel();
    void updateMenu(const QList<QString> &list);

private:

    QGridLayout *m_mainLayout;
    QLabel* m_welcomeLogo;
    ILineEdit *m_inputLine;

    IVPushCard *card1;
    IVPushCard *card2;
    IVPushCard *card3;
    IVPushCard *card4;

    QMenu* m_menu;

    void setupConnections();
    void applyStyleSheet();
};

#endif // IWELCOMEPAGE_H
