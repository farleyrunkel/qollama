#ifndef IWELCOMEPAGE_H
#define IWELCOMEPAGE_H

#include <QLabel>
#include <QGridLayout>

#include "ilineedit.h"
#include "ivpushcard.h"
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

    void setupConnections();
    void updateMenu(const QList<QString> &list);

private:

    QGridLayout *m_mainLayout;
    QLabel* m_welcomeLogo;
    ILineEdit *m_inputLine;

    IVPushCard *m_card1;
    IVPushCard *m_card2;
    IVPushCard *m_card3;
    IVPushCard *m_card4;

    QMenu* m_menu;
};

#endif // IWELCOMEPAGE_H
