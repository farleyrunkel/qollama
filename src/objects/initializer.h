#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <QObject>
#include <configmanager.h>

class Initializer : public QObject {
    Q_OBJECT

public:
    Initializer(QObject* parent = nullptr) : QObject(parent) {
       // connect(&dataLoader, &DataLoader::dataLoaded, this, &Initializer::onDataLoaded);
    }

    void initialize() {
        // 加载配置文件
        // IConfigManager::instance().loadInitialData();

        // 异步加载数据
        // dataLoader.loadData();
    }

private slots:
    void onDataLoaded() {
        // 数据加载完成后的处理逻辑
    }

private:
    // DataLoader dataLoader;
};

#endif // INITIALIZER_H
