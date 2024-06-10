#include "configmanager.h"
#include <QFile>

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

// Initialize default configuration values
void ConfigManager::initializeDefaults() {
    // Set default values

    m_appIcon = QPixmap(":/icon.png");
    m_username = "QOllama"; // Default username

    // Store default configurations
    setConfig("username", m_username);
    setConfig("appIcon", m_appIcon);
    setConfig("avatar", "://icon/farley.jpg");
    setConfig("modeldir", "C:/Users/95439/Documents/Github/qollama/models");
    setConfig("ollamaport", "localhost:11434");

    // Emit signals to notify about changes
    emit onAvatarChanged();
    emit usernameChanged(m_username);
}
