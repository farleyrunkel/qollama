#include "isettingpage.h"
#include "configmanager.h"

ISettingPage::ISettingPage(QWidget *parent) : QWidget(parent) {
    setupUi();
    setupConnections();
}

void ISettingPage::setupUi() {
    mainLayout = new QVBoxLayout(this);

    avatarLabel = new QLabel(this);
    avatarLabel->setFixedSize(100, 100);
    avatarLabel->setAlignment(Qt::AlignCenter);
    avatarLabel->setPixmap(ConfigManager::instance().avatar().scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    changeAvatarButton = new QPushButton("更改头像", this);
    changeAvatarButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #5cb85c;"
        "    color: white;"
        "    border-radius: 5px;"
        "    padding: 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #4cae4c;"
        "}"
        );

    usernameLineEdit = new QLineEdit(this);
    usernameLineEdit->setPlaceholderText("输入用户名");
    usernameLineEdit->setText(ConfigManager::instance().username());
    usernameLineEdit->setStyleSheet(
        "QLineEdit {"
        "    padding: 10px;"
        "    border: 1px solid #ccc;"
        "    border-radius: 5px;"
        "}"
        );

    saveButton = new QPushButton("保存", this);
    saveButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #337ab7;"
        "    color: white;"
        "    border-radius: 5px;"
        "    padding: 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #286090;"
        "}"
        );

    mainLayout->setSpacing(20);
    mainLayout->addWidget(avatarLabel, 0, Qt::AlignCenter);
    mainLayout->addWidget(changeAvatarButton, 0, Qt::AlignCenter);
    mainLayout->addWidget(usernameLineEdit);
    mainLayout->addWidget(saveButton, 0, Qt::AlignCenter);
}

void ISettingPage::setupConnections() {
    connect(changeAvatarButton, &QPushButton::clicked, this, &ISettingPage::changeAvatar);
    connect(saveButton, &QPushButton::clicked, this, &ISettingPage::changeUsername);

    connect(&ConfigManager::instance(), &ConfigManager::avatarChanged, this, &ISettingPage::updateAvatarDisplay);
    connect(&ConfigManager::instance(), &ConfigManager::usernameChanged, this, &ISettingPage::updateUsernameDisplay);
}

void ISettingPage::changeAvatar() {
    QString fileName = QFileDialog::getOpenFileName(this, "选择头像", "", "图片文件 (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty()) {
        QPixmap newAvatar(fileName);
        ConfigManager::instance().setAvatar(newAvatar);
    }
}

void ISettingPage::changeUsername() {
    QString newUsername = usernameLineEdit->text();
    if (!newUsername.isEmpty()) {
        ConfigManager::instance().setUsername(newUsername);
    }
}

void ISettingPage::updateAvatarDisplay(const QPixmap &newAvatar) {
    avatarLabel->setPixmap(newAvatar.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void ISettingPage::updateUsernameDisplay(const QString &newUsername) {
    usernameLineEdit->setText(newUsername);
}
