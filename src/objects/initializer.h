#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <QObject>
#include <QApplication>
#include <configmanager.h>
#include <signalhub.h>
#include "stylemanager.h"
#include <QMainWindow>

class Initializer : public QObject {
    Q_OBJECT

public:
    Initializer(QObject* parent = nullptr);

    void initialize(QMainWindow* window);

signals:
    void initializationComplete();

private slots:
    void onDataLoaded();

private:
    //DataLoader dataLoader;
    StyleManager styleManager;
    QMainWindow* mainWindow;
};

#endif // INITIALIZER_H
