#include "isettingpage.h"
#include "iconfigmanager.h"

ISettingPage::ISettingPage(QWidget *parent) : QWidget(parent)
{
    setupUi();
    setupConnections();
}

void ISettingPage::setupUi()
{
    mainLayout = new QVBoxLayout(this);

    // 头像显示
    avatarLabel = new QLabel(this);
    avatarLabel->setFixedSize(100, 100);
    avatarLabel->setAlignment(Qt::AlignCenter);
    avatarLabel->setPixmap(IConfigManager::instance().getAvatar().scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // 更改头像按钮
    changeAvatarButton = new QPushButton("更改头像", this);

    // 用户名输入框
    usernameLineEdit = new QLineEdit(this);
    usernameLineEdit->setPlaceholderText("输入用户名");
    usernameLineEdit->setText(IConfigManager::instance().getUsername());

    // 保存按钮
    saveButton = new QPushButton("保存", this);

    // 添加到主布局
    mainLayout->addWidget(avatarLabel);
    mainLayout->addWidget(changeAvatarButton);
    mainLayout->addWidget(usernameLineEdit);
    mainLayout->addWidget(saveButton);
}

void ISettingPage::setupConnections()
{
    connect(changeAvatarButton, &QPushButton::clicked, this, &ISettingPage::changeAvatar);
    connect(saveButton, &QPushButton::clicked, this, &ISettingPage::changeUsername);

    // 连接 IConfigManager 信号以更新界面
    connect(&IConfigManager::instance(), &IConfigManager::avatarChanged, this, &ISettingPage::updateAvatarDisplay);
    connect(&IConfigManager::instance(), &IConfigManager::usernameChanged, this, &ISettingPage::updateUsernameDisplay);
}

void ISettingPage::changeAvatar()
{
    QString fileName = QFileDialog::getOpenFileName(this, "选择头像", "", "图片文件 (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty()) {
        QPixmap newAvatar(fileName);
        IConfigManager::instance().setAvatar(newAvatar);
    }
}

void ISettingPage::changeUsername()
{
    QString newUsername = usernameLineEdit->text();
    if (!newUsername.isEmpty()) {
        IConfigManager::instance().setUsername(newUsername);
    }
}

void ISettingPage::updateAvatarDisplay(const QPixmap& newAvatar)
{
    avatarLabel->setPixmap(newAvatar.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void ISettingPage::updateUsernameDisplay(const QString& newUsername)
{
    usernameLineEdit->setText(newUsername);
}
