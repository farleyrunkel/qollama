#ifndef INITIALIZER_H
#define INITIALIZER_H

#include "stylemanager.h"
#include <QApplication>
#include <QMainWindow>
#include <QObject>
#include <configmanager.h>
#include <signalhub.h>

class Initializer : public QObject {
    Q_OBJECT

public:
    Initializer(QObject *parent = nullptr);

    void initialize(QMainWindow *window);

signals:
    void initializationComplete();

private slots:
    void onDataLoaded();

private:
    // DataLoader dataLoader;
    StyleManager styleManager;
    QMainWindow *mainWindow;
};

#endif // INITIALIZER_H
