#ifndef ICONFIGMANAGER_H
#define ICONFIGMANAGER_H

#include <QObject>
#include <QPixmap>
#include <QVariant>
#include <QMap>

class ConfigManager : public QObject
{
    Q_OBJECT

public:
    static ConfigManager& instance() {
        static ConfigManager instance;
        return instance;
    }

    QPixmap appIcon() const { return m_appIcon; }
    QPixmap avatar() const { return m_userAvatar; }
    void setAvatar(const QPixmap& newAvatar) {
        m_userAvatar = newAvatar;
        emit avatarChanged(m_userAvatar);
    }

    QString username() const { return m_username; }
    void setUsername(const QString& newUsername) {
        m_username = newUsername;
        emit usernameChanged(m_username);
    }

    QVariant value(const QString& key) const {
        return configs.value(key);
    }

    void setConfig(const QString& key, const QVariant& value) {
        configs[key] = value;
        emit configChanged(key, value);
    }
    void initializeDefaults();

signals:
    void avatarChanged(const QPixmap& newAvatar);
    void usernameChanged(const QString& newUsername);
    void configChanged(const QString& key, const QVariant& value);

private:
    ConfigManager() { initializeDefaults(); }
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;

private:
    QPixmap m_appIcon;
    QPixmap m_userAvatar;
    QString m_username;
    QMap<QString, QVariant> configs;
};

#endif // ICONFIGMANAGER_H
