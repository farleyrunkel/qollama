#include "configmanager.h"
#include <QFile>

void ConfigManager::initializeDefaults() {

    m_userAvatar = QPixmap("://icon.png");
    m_appIcon = QPixmap("://icon.png");
    m_username = "QOllama"; // 您可以在这里设置默认用户名

    setConfig("username", m_username);
    setConfig("appIcon", m_appIcon);
    setConfig("userAvatar", m_userAvatar);

    // 发出信号通知
    emit avatarChanged(m_userAvatar);
    emit usernameChanged(m_username);
}
