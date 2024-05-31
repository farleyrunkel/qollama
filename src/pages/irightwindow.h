#ifndef RIGHTWINDOW_H
#define RIGHTWINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QPushButton>

class IRightWindow : public QWidget
{
    Q_OBJECT
public:
    IRightWindow();

    QStackedWidget* pages() {return m_pages;}
    void setLeftWidget(QWidget *widget);
    void setRightWidget(QWidget *widget);

private:

    void setupUi();
    QHBoxLayout*  mainLayout ;

   QVBoxLayout*  leftWidget   ;
   QVBoxLayout*  rightWidget    ;

  QStackedWidget*  m_pages  ;

   QPushButton* expandButton;
  QPushButton* userButton;
};

#endif // RIGHTWINDOW_H
