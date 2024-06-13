#include "initializer.h"
#include "dataloader.h"

Initializer::Initializer(QObject *parent)
    : QObject(parent), mainWindow(nullptr) {
    connect(&DataLoader::instance(), &DataLoader::dataLoaded, this,
            &Initializer::onDataLoaded);
}

void Initializer::initialize(QMainWindow *window) {
    mainWindow = window;

    ConfigManager::instance().initializeDefaults();

    // 指定要加载的目录路径
    QString directoryPath =
        ConfigManager::instance().config("gptsdir").toString() + "/prompts";
    DataLoader::instance().loadData(directoryPath);
}

void Initializer::onDataLoaded() {
    styleManager.loadStyleSheet(":/qss/style.qss");

    // styleManager.enableBorders(true);

    styleManager.applyStyleSheet(mainWindow);
    styleManager.applyPalette(mainWindow);

    mainWindow->show();

    emit initializationComplete();
}
