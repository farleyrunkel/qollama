#include "isettingpage.h"
#include "configmanager.h"
#include "signalhub.h"
#include <QApplication>
#include <QCalendarWidget>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QPainter>
#include <QStackedWidget>
#include <QTabWidget>
#include <stylemanager.h>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

// Constructor
ISettingPage::ISettingPage(QWidget *parent) : QDialog(parent) {
    setupMainLayout();      // Setup the main layout
    setupSideArea();        // Setup the top area
    setupSettingsAccount(m_settingLayout); // Setup the setting area
    setupConnections();     // Setup signal-slot
}

void ISettingPage::showEvent(QShowEvent *event) {
    QDialog::showEvent(event);
    QWidget *parent = qobject_cast<QWidget *>(this->parent());

    if (parent) {
        // 获取父窗口的全局屏幕坐标
        QPoint globalPos = parent->mapToGlobal(QPoint(0, 0));

        // 父窗口的宽度和高度
        int parentWidth = parent->width();
        int parentHeight = parent->height();

        // ISettingPage 的宽度和高度（为父窗口的 80%）
        int width = parentWidth * 1;
        int height = parentHeight * 1;

        // 计算 ISettingPage 的左上角坐标，使其居中于父窗口
        int x = globalPos.x() + (parentWidth - width) / 2;
        int y = globalPos.y() + (parentHeight - height) / 2;

#ifdef Q_OS_WIN
        // 获取系统标题栏高度
        int titleBarHeight = GetSystemMetrics(SM_CYCAPTION);
        y -= titleBarHeight;
        height += titleBarHeight;
#endif

        // 设置 ISettingPage 的位置和大小
        setGeometry(x, y, width, height);
    }
}

void ISettingPage::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 设置灰色半透明背景
    QColor backgroundColor(128, 128, 128,
                           128); // RGB(128, 128, 128) 是灰色，最后一个参数 128
        // 是透明度，范围是 0-255
    painter.fillRect(this->rect(), backgroundColor);
}

// Setup the main layout of the setting page
void ISettingPage::setupMainLayout() {
    setObjectName("ISettingPage");
    setContentsMargins(80, 80, 80, 80);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    m_mainLayout = new QHBoxLayout(this);
    setLayout(m_mainLayout);
    auto m_centerWidget = new QWidget;
    m_centerWidget->setObjectName("settingCenterWidget");
    m_centerWidget->setAutoFillBackground(true);

    StyleManager::applyPalette(m_centerWidget);

    m_mainLayout->addWidget(m_centerWidget);

    auto m_centerLayout = new QHBoxLayout;
    m_centerWidget->setLayout(m_centerLayout);

    m_sideArea = new QWidget(m_centerWidget);
    m_sideArea->setFixedWidth(130);

    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);

    m_settingLayout = new QStackedLayout;

    auto m_right = new QGridLayout;
    m_right->addWidget(new QLabel("Account"), 0, 0);

    QPushButton *closeButton = new QPushButton("x");
    closeButton->setFixedSize(QSize(30, 30));
    closeButton->setObjectName("smallButton");
    m_right->addWidget(closeButton, 0, 1);
    connect(closeButton, &QPushButton::clicked, this, &QWidget::close);

    // 添加分隔线
    QFrame *line1 = new QFrame();
    line1->setFrameShape(QFrame::HLine);
    line1->setFrameShadow(QFrame::Sunken);

    m_right->addWidget(line1, 1, 0, 1, 2);
    m_right->addLayout(m_settingLayout, 2, 0, 1, 2);

    m_centerLayout->addWidget(m_sideArea);
    m_centerLayout->addWidget(line);

    m_centerLayout->addLayout(m_right);
}

// Setup the top area of the setting page
void ISettingPage::setupSideArea() {
    auto sideAreaLayout = new QVBoxLayout(m_sideArea);
    sideAreaLayout->setContentsMargins(5, 8, 5, 10);
    sideAreaLayout->setAlignment(Qt::AlignTop);

    sideAreaLayout->addWidget(new QLabel("Settings"));

    m_accountButton = new QPushButton(QIcon("://icon/account.svg"), "Account");
    m_accountButton->setObjectName("bigButton");
    m_accountButton->setFixedHeight(30);
    sideAreaLayout->addWidget(m_accountButton);
}

QGroupBox* ISettingPage::addSettingGroupBox(const QString& key, const QString& value, const QString& config) {
    auto groupBox = new QGroupBox(key);
    auto lineEdit  = new QLineEdit(value);
    auto pushButton = new QPushButton("Edit");

    lineEdit->setDisabled(true);
    lineEdit->setFrame(false);
    pushButton->setObjectName("smallButton");

    groupBox->setStyleSheet("QGroupBox { border: 0px; background-color: white; }");
    groupBox->setLayout(new QHBoxLayout);
    groupBox->layout()->setContentsMargins(11, 21, 11, 21);

    groupBox->layout()->addWidget(lineEdit);
    groupBox->layout()->addWidget(pushButton);

    connect(pushButton, &QPushButton::clicked, this, [lineEdit, pushButton, config]() {
        lineEdit->setEnabled(!lineEdit->isEnabled());
        pushButton->setText(lineEdit->isEnabled() ? "Done" : "Edit");
        if (!config.isEmpty() && pushButton->text() == "Done") {
            emit ConfigManager::instance().configChanged(config, lineEdit->text());
        }
    });

    return groupBox;
}

// Setup the setting area of the setting page
void ISettingPage::setupSettingsAccount(QLayout* layout) {
    auto account = new QWidget;
    m_settings["account"] = account;
    layout->addWidget(m_settings["account"]);

    auto accountLayout = new QVBoxLayout(m_settings["account"]);
    accountLayout->setSpacing(10);

    QPixmap avatar(ConfigManager::instance().config("avatar").toString());
    avatar = StyleManager::roundedPixmap(avatar);

    m_changeAvatarButton = new QPushButton(this);
    m_changeAvatarButton->setFixedSize(100, 100);
    m_changeAvatarButton->setStyleSheet("border: 2px solid black; border-radius: 50px;");
    m_changeAvatarButton->setIcon(QIcon(avatar));
    m_changeAvatarButton->setIconSize(QSize(100, 100));


    QHBoxLayout *lay = new QHBoxLayout;
    lay->addWidget(m_changeAvatarButton);
    lay->addWidget(addSettingGroupBox("User name", "QOllama", "username"));

    accountLayout->addLayout(lay);
    accountLayout->addWidget(addSettingGroupBox("Model files directory", ConfigManager::instance().config("modeldir").toString(), "modeldir"));
    accountLayout->setAlignment(Qt::AlignTop);
}

// Setup signal-slot connections
void ISettingPage::setupConnections() {
    connect(m_changeAvatarButton, &QPushButton::clicked, this,
            &ISettingPage::changeAvatar); // Change avatar button clicked
    // connect(m_saveButton, &QPushButton::clicked, this,
    //         &ISettingPage::changeUsername); // Save button clicked

    // connect(&ConfigManager::instance(), &ConfigManager::avatarChanged, this,
    //         &ISettingPage::updateAvatarDisplay); // Avatar changed signal
    // connect(&ConfigManager::instance(), &ConfigManager::usernameChanged, this,
    //         &ISettingPage::updateUsernameDisplay); // Username changed signal

    // connect(m_accountButton, &QPushButton::clicked, &SignalHub::instance(),
    //         &SignalHub::onExpandButtonClicked);
}

// Slot to change avatar
void ISettingPage::changeAvatar() {
    QString fileName = QFileDialog::getOpenFileName(
        this, "Select Avatar", "", "Image Files (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty()) {
        QPixmap newAvatar(fileName);
        m_changeAvatarButton->setIcon(QIcon(newAvatar));
        ConfigManager::instance().setConfig("avatar", fileName);
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
    // m_avatarLabel->setPixmap(newAvatar.scaled(100, 100,
    // Qt::KeepAspectRatio,Qt::SmoothTransformation));
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
