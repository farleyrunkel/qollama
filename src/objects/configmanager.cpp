#include "configmanager.h"
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

// Get the singleton instance of ConfigManager
ConfigManager &ConfigManager::instance() {
    static ConfigManager instance;
    return instance;
}

// Get application icon
QPixmap ConfigManager::appIcon() const { return m_appIcon; }

// Set username and emit signal
void ConfigManager::setUsername(const QString &newUsername) {
    m_username = newUsername;
    emit usernameChanged(m_username);
}

// Get configuration config by key
QVariant ConfigManager::config(const QString &key) const {
    return m_configs.value(key);
}

// Set configuration value by key and emit signal
void ConfigManager::setConfig(const QString &key, const QVariant &value) {
    m_configs[key] = value;
    emit configChanged(key, value);
}

// Initialize configuration values from config.json file
void ConfigManager::initializeDefaults() {
    // Set default values
    m_appIcon = QPixmap(":/images/icon.png");
    m_username = "You"; // Default username

    // Search for config.json in current and parent directories
    QString configPath = findConfigFile();
    if (!configPath.isEmpty()) {
        qDebug() << "configPath" << configPath;

        readConfigFromFile(configPath);
    }

    // Emit signals to notify about changes
    emit onAvatarChanged();
    emit usernameChanged(m_username);
}

// Helper function to search for config.json file
QString ConfigManager::findConfigFile() const {
    QDir currentDir = QDir::current();
    QDir parentDir = currentDir;
    qDebug() << "currentDir" << currentDir;
    // Search in current directory and its parent
    for (int i = 0; i < 2; ++i) {
        if (currentDir.exists("config.json")) {
            return currentDir.filePath("config.json");
        }
        parentDir.cdUp();
        currentDir = parentDir;
    }

    return QString(); // Config file not found
}

// Helper function to read config.json file
void ConfigManager::readConfigFromFile(const QString &filePath) {
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QByteArray jsonData = file.readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
        if (!jsonDoc.isNull() && jsonDoc.isObject()) {
            QJsonObject jsonObj = jsonDoc.object();
            qDebug() << "jsonObj" << jsonObj;

            // Read username
            if (jsonObj.contains("username")) {
                QString username = jsonObj.value("username").toString();
                m_username = username;
                setConfig("username", username);
            }

            // Read app icon
            if (jsonObj.contains("appIcon")) {
                QString appIconPath = jsonObj.value("appIcon").toString();
                m_appIcon = QPixmap(appIconPath);
                setConfig("appIcon", appIconPath);
            }

            // Read avatar
            if (jsonObj.contains("avatar")) {
                QString avatarPath = jsonObj.value("avatar").toString();
                setConfig("avatar", avatarPath);
            }

            // Read ollama port
            if (jsonObj.contains("ollamaport")) {
                QString ollamaPort = jsonObj.value("ollamaport").toString();
                auto m_ollamaPort = ollamaPort;
                setConfig("ollamaport", m_ollamaPort);
            }

            // Read model directory
            if (jsonObj.contains("modeldir")) {
                QString modelDir = jsonObj.value("modeldir").toString();
                auto m_modelDir = modelDir;
                setConfig("modeldir", m_modelDir);
            }
        }
        file.close();
    }
}
