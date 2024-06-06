#include "initializer.h"
#include "signalhub.h"

Initializer::Initializer(QObject *parent)
    : QObject(parent), mainWindow(nullptr) {
    // connect(&dataLoader, &DataLoader::dataLoaded, this,
    // &Initializer::onDataLoaded);
}

void Initializer::initialize(QMainWindow *window) {
    mainWindow = window;

    ConfigManager::instance().initializeDefaults();

    onDataLoaded();

    emit SignalHub::instance().listRequest();

    // dataLoader.loadData();
}

void Initializer::onDataLoaded() {
    styleManager.loadStyleSheet(":/qss/style.qss");

    // styleManager.enableBorders(true);

    styleManager.applyStyleSheet(mainWindow);

    mainWindow->show();

    emit initializationComplete();
}
