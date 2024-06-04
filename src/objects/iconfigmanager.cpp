#include "iconfigmanager.h"
#include <QFile>

void IConfigManager::initializeDefaults() {
    // 设置默认头像
    QString defaultAvatarPath = "://icon/qollama.png"; // 假设默认头像存储在资源文件中
    if (QFile::exists(defaultAvatarPath)) {
        avatar = QPixmap(defaultAvatarPath);
    } else {
        avatar = QPixmap(30, 30); // 创建一个空的默认头像
        avatar.fill(Qt::gray); // 用灰色填充
    }

    app = QPixmap("://icon/qollama.png");
    // 设置默认用户名
    username = "QOllama"; // 您可以在这里设置默认用户名

    // 发出信号通知
    emit avatarChanged(avatar);
    emit usernameChanged(username);
}
