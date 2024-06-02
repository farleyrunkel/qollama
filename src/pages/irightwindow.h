#ifndef RIGHTWINDOW_H
#define RIGHTWINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QPushButton>
#include "iwidget.h"

class IRightWindow : public QWidget
{
    Q_OBJECT

    INJECT_SHOW_HIDE_EVENTS(IRightWindow)

public:
    IRightWindow();

    QStackedWidget* pages() {return m_pages;}
    void setLeftWidget(QWidget *widget);
    void setRightWidget(QWidget *widget);

    QPushButton* expandButton() {return m_expandButton;}

    QPushButton* userButton() {return m_userButton;};
private:

    void setupUi();
    QHBoxLayout*  mainLayout ;

    QVBoxLayout*  leftWidget   ;
    QVBoxLayout*  rightWidget    ;

    QStackedWidget*  m_pages  ;

    QPushButton* m_expandButton;
    QPushButton* m_userButton;
};

#endif // RIGHTWINDOW_H
