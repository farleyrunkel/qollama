#ifndef ILEFTWINDOW_H
#define ILEFTWINDOW_H

#include <QWidget>

class ILeftWindow: public QWidget
{
    Q_OBJECT
public:
    ILeftWindow(QWidget* parent = nullptr);;

    void setupUi();
};

#endif // ILEFTWINDOW_H
