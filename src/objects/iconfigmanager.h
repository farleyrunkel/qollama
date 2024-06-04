#ifndef ICONFIGMANAGER_H
#define ICONFIGMANAGER_H

#include <QObject>
#include <QPixmap>
#include <QVariant>
#include <QMap>

class IConfigManager : public QObject
{
    Q_OBJECT

public:
    static IConfigManager& instance() {
        static IConfigManager instance;
        return instance;
    }

    QPixmap getAvatar() const { return avatar; }
    void setAvatar(const QPixmap& newAvatar) {
        avatar = newAvatar;
        emit avatarChanged(avatar);
    }

    QString getUsername() const { return username; }
    void setUsername(const QString& newUsername) {
        username = newUsername;
        emit usernameChanged(username);
    }

    QVariant getConfig(const QString& key) const {
        return configs.value(key);
    }

    void setConfig(const QString& key, const QVariant& value) {
        configs[key] = value;
        emit configChanged(key, value);
    }

signals:
    void avatarChanged(const QPixmap& newAvatar);
    void usernameChanged(const QString& newUsername);
    void configChanged(const QString& key, const QVariant& value);

private:
    IConfigManager() { initializeDefaults(); }
    IConfigManager(const IConfigManager&) = delete;
    IConfigManager& operator=(const IConfigManager&) = delete;

    void initializeDefaults();
    QPixmap avatar;
    QString username;
    QMap<QString, QVariant> configs;
};

#endif // ICONFIGMANAGER_H
