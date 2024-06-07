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

    // Get username
    QString username() const { return m_username; }

    // Set username and emit signal
    void setUsername(const QString &newUsername);

    // Get configuration config by key
    QVariant config(const QString &key) const;

    // Set configuration value by key and emit signal
    void setConfig(const QString &key, const QVariant &value);

    // Initialize default configuration values
    void initializeDefaults();

signals:
    // Signal emitted when avatar changes
    void avatarChanged(const QString &newAvatar);

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
    QString m_username;                // Username
    QMap<QString, QVariant> m_configs; // Configuration key-value pairs
};

#endif // ICONFIGMANAGER_H
