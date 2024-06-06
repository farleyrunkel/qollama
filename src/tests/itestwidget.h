#ifndef ITESTWIDGET_H
#define ITESTWIDGET_H

#include <QDialog>

class ITestWidget : public QDialog {
    Q_OBJECT
public:
    explicit ITestWidget(QWidget *parent = nullptr);

signals:
};

#endif // ITESTWIDGET_H
