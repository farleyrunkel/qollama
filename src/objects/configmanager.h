#ifndef ICONFIGMANAGER_H
#define ICONFIGMANAGER_H

#include <QMap>
#include <QObject>
#include <QPixmap>
#include <QVariant>

class ConfigManager : public QObject {
    Q_OBJECT

public:
    // Get the singleton instance of ConfigManager
    static ConfigManager &instance();

    // Get application icon
    QPixmap appIcon() const;

    // Get user avatar
    QPixmap avatar() const;

    // Set user avatar and emit signal
    void setAvatar(const QPixmap &newAvatar);

    // Get username
    QString username() const { return m_username; }

    // Set username and emit signal
    void setUsername(const QString &newUsername);

    // Get configuration value by key
    QVariant value(const QString &key) const;

    // Set configuration value by key and emit signal
    void setConfig(const QString &key, const QVariant &value);

    // Initialize default configuration values
    void initializeDefaults();

signals:
    // Signal emitted when avatar changes
    void avatarChanged(const QPixmap &newAvatar);

    // Signal emitted when username changes
    void usernameChanged(const QString &newUsername);

    // Signal emitted when any configuration value changes
    void configChanged(const QString &key, const QVariant &value);

private:
    // Private constructor for singleton pattern
    ConfigManager() { initializeDefaults(); }

    // Disable copy constructor and assignment operator
    ConfigManager(const ConfigManager &) = delete;
    ConfigManager &operator=(const ConfigManager &) = delete;

private:
    // Member variables
    QPixmap m_appIcon;                 // Application icon
    QPixmap m_userAvatar;              // User avatar
    QString m_username;                // Username
    QMap<QString, QVariant> m_configs; // Configuration key-value pairs
};

#endif // ICONFIGMANAGER_H
