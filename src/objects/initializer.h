#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <QObject>
#include <QApplication>
#include <configmanager.h>
#include <signalhub.h>
#include "stylemanager.h"
#include <QMainWindow>
#include "signalhub.h"

class Initializer : public QObject {
    Q_OBJECT

public:
    Initializer(QObject* parent = nullptr) : QObject(parent), mainWindow(nullptr) {
        // connect(&dataLoader, &DataLoader::dataLoaded, this, &Initializer::onDataLoaded);
    }

    void initialize(QMainWindow* window) {

        mainWindow = window;

        ConfigManager::instance().initializeDefaults();

        onDataLoaded();

        emit SignalHub::instance().listRequest();
        //dataLoader.loadData();
    }

signals:
    void initializationComplete();

private slots:
    void onDataLoaded() {


        styleManager.loadStyleSheet(":/qss/style.qss");
        styleManager.applyStyleSheet(mainWindow);

        mainWindow->show();

        emit initializationComplete();
    }

private:
    //DataLoader dataLoader;
    StyleManager styleManager;
    QMainWindow* mainWindow;
};

#endif // INITIALIZER_H
