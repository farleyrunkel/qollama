#include "configmanager.h"
#include <QFile>

// Get the singleton instance of ConfigManager
ConfigManager &ConfigManager::instance() {
    static ConfigManager instance;
    return instance;
}

// Get application icon
QPixmap ConfigManager::appIcon() const { return m_appIcon; }

// Get user avatar
QPixmap ConfigManager::avatar() const { return m_userAvatar; }

// Set user avatar and emit signal
void ConfigManager::setAvatar(const QPixmap &newAvatar) {
    m_userAvatar = newAvatar;
    emit avatarChanged(m_userAvatar);
}

// Set username and emit signal
void ConfigManager::setUsername(const QString &newUsername) {
    m_username = newUsername;
    emit usernameChanged(m_username);
}

// Get configuration value by key
QVariant ConfigManager::value(const QString &key) const {
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
    m_userAvatar = QPixmap(":/icon.png");
    m_appIcon = QPixmap(":/icon.png");
    m_username = "QOllama"; // Default username

    // Store default configurations
    setConfig("username", m_username);
    setConfig("appIcon", m_appIcon);
    setConfig("userAvatar", m_userAvatar);
    setConfig("modelsDir", "   ");

    // Emit signals to notify about changes
    emit avatarChanged(m_userAvatar);
    emit usernameChanged(m_username);
}
