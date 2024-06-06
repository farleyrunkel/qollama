#include "isettingpage.h"
#include "signalhub.h"
#include "configmanager.h"

// Constructor
ISettingPage::ISettingPage(QWidget *parent) : QWidget(parent) {
    setupMainLayout();  // Setup the main layout
    setupTopArea();     // Setup the top area
    setupSettingArea(); // Setup the setting area
    setupConnections(); // Setup signal-slot connections
}

// Setup the main layout of the setting page
void ISettingPage::setupMainLayout() {
    setObjectName("ISettingPage");
    setContentsMargins(0, 0, 0, 0);

    m_mainLayout = new QVBoxLayout(this);
    setLayout(m_mainLayout);

    m_topArea = new QWidget(this);
    m_topArea->setFixedHeight(35);

    m_settingLayout = new QVBoxLayout;

    m_mainLayout->addWidget(m_topArea);
    m_mainLayout->addLayout(m_settingLayout);
}

// Setup the top area of the setting page
void ISettingPage::setupTopArea() {
    auto topAreaLayout = new QHBoxLayout(m_topArea);
    topAreaLayout->setContentsMargins(0, 0, 0, 0);

    m_expandButton = createButton("://icon/sidebar-left.svg");
    m_newChatButton = createButton(":/icon/create-new.svg");
    m_userButton = createButton("://icon.png");

    m_expandButton->hide();
    m_newChatButton->hide();
    m_userButton->hide();

    topAreaLayout->addWidget(m_expandButton);
    topAreaLayout->addWidget(m_newChatButton);
    topAreaLayout->addStretch(1);
    topAreaLayout->addWidget(m_userButton);
}

// Setup the setting area of the setting page
void ISettingPage::setupSettingArea() {
    m_avatarLabel = new QLabel(this);
    m_avatarLabel->setFixedSize(100, 100);
    m_avatarLabel->setAlignment(Qt::AlignCenter);
    m_avatarLabel->setPixmap(ConfigManager::instance().avatar().scaled(
        100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    m_changeAvatarButton = new QPushButton("Change Avatar", this);
    m_changeAvatarButton->setStyleSheet("QPushButton {"
                                        "    background-color: #5cb85c;"
                                        "    color: white;"
                                        "    border-radius: 5px;"
                                        "    padding: 10px;"
                                        "}"
                                        "QPushButton:hover {"
                                        "    background-color: #4cae4c;"
                                        "}");

    m_usernameLineEdit = new QLineEdit(this);
    m_usernameLineEdit->setPlaceholderText("Enter Username");
    m_usernameLineEdit->setText(ConfigManager::instance().username());
    m_usernameLineEdit->setStyleSheet("QLineEdit {"
                                      "    padding: 10px;"
                                      "    border: 1px solid #ccc;"
                                      "    border-radius: 5px;"
                                      "}");

    m_saveButton = new QPushButton("Save", this);
    m_saveButton->setStyleSheet("QPushButton {"
                                "    background-color: #337ab7;"
                                "    color: white;"
                                "    border-radius: 5px;"
                                "    padding: 10px;"
                                "}"
                                "QPushButton:hover {"
                                "    background-color: #286090;"
                                "}");

    m_settingLayout->setSpacing(20);
    m_settingLayout->addWidget(m_avatarLabel, 0, Qt::AlignCenter);
    m_settingLayout->addWidget(m_changeAvatarButton, 0, Qt::AlignCenter);
    m_settingLayout->addWidget(m_usernameLineEdit);
    m_settingLayout->addWidget(m_saveButton, 0, Qt::AlignCenter);
}

// Setup signal-slot connections
void ISettingPage::setupConnections() {
    connect(m_changeAvatarButton, &QPushButton::clicked, this,
            &ISettingPage::changeAvatar); // Change avatar button clicked
    connect(m_saveButton, &QPushButton::clicked, this,
            &ISettingPage::changeUsername); // Save button clicked

    connect(&ConfigManager::instance(), &ConfigManager::avatarChanged, this,
            &ISettingPage::updateAvatarDisplay); // Avatar changed signal
    connect(&ConfigManager::instance(), &ConfigManager::usernameChanged, this,
            &ISettingPage::updateUsernameDisplay); // Username changed signal

    connect(m_newChatButton, &QPushButton::clicked, &SignalHub::instance(),
            &SignalHub::onNewChatButtonClicked);

    connect(m_expandButton, &QPushButton::clicked, &SignalHub::instance(),
            &SignalHub::onExpandButtonClicked);
    connect(&SignalHub::instance(), &SignalHub::onSideAreaHidden, m_expandButton,
            &QPushButton::setVisible);
    connect(&SignalHub::instance(), &SignalHub::onSideAreaHidden, m_newChatButton,
            &QPushButton::setVisible);
    connect(&SignalHub::instance(), &SignalHub::onSideAreaHidden, m_userButton,
            &QPushButton::setVisible);
}

// Slot to change avatar
void ISettingPage::changeAvatar() {
    QString fileName = QFileDialog::getOpenFileName(
        this, "Select Avatar", "", "Image Files (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty()) {
        QPixmap newAvatar(fileName);
        ConfigManager::instance().setAvatar(newAvatar); // Update avatar in config
    }
}

// Slot to change username
void ISettingPage::changeUsername() {
    QString newUsername = m_usernameLineEdit->text();
    if (!newUsername.isEmpty()) {
        ConfigManager::instance().setUsername(
            newUsername); // Update username in config
    }
}

// Slot to update avatar display
void ISettingPage::updateAvatarDisplay(const QPixmap &newAvatar) {
    m_avatarLabel->setPixmap(newAvatar.scaled(100, 100, Qt::KeepAspectRatio,
                                              Qt::SmoothTransformation));
}

// Slot to update username display
void ISettingPage::updateUsernameDisplay(const QString &newUsername) {
    m_usernameLineEdit->setText(newUsername);
}

// Slot to handle expand button click
void ISettingPage::expandSettings() {
    // Handle expand button click
    // Implement functionality here
}

// Slot to handle new setting button click
void ISettingPage::addNewSetting() {
    // Handle new setting button click
    // Implement functionality here
}

// Slot to handle user button click
void ISettingPage::userSettings() {
    // Handle user button click
    // Implement functionality here
}

// Create a button with an icon
QPushButton *ISettingPage::createButton(const QString &iconPath) {
    auto button = new QPushButton;
    button->setIcon(QIcon(iconPath));
    button->setFixedSize(QSize(30, 30));
    button->setObjectName("smallButton");
    return button;
}
