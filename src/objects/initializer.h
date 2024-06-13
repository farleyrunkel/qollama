#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <QApplication>
#include <QMainWindow>
#include <QObject>
#include <configmanager.h>
#include <signalhub.h>

class Initializer : public QObject {
    Q_OBJECT

public:
    Initializer(QObject *parent = nullptr);

    void initialize();

signals:
    void initializationComplete();

private slots:
    void onDataLoaded();

private:

};

#endif // INITIALIZER_H
