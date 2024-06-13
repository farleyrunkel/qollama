#include "initializer.h"
#include "dataloader.h"
#include "stylemanager.h"

Initializer::Initializer(QObject *parent)
    : QObject(parent) {
    connect(&DataLoader::instance(), &DataLoader::dataLoaded, this,
            &Initializer::onDataLoaded);
}

void Initializer::initialize() {

    ConfigManager::instance().initializeDefaults();

    // 指定要加载的目录路径
    QString directoryPath =
        ConfigManager::instance().config("gptsdir").toString() + "/prompts";
    DataLoader::instance().loadData(directoryPath);
}

void Initializer::onDataLoaded() {

    emit initializationComplete();
}
