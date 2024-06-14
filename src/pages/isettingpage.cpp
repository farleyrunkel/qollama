#include "isettingpage.h"
#include "configmanager.h"
#include <QApplication>
#include <QCalendarWidget>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QStackedWidget>
#include <QTabWidget>
#include <stylemanager.h>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

ISettingPage::ISettingPage(QWidget *parent) : QDialog(parent) {
    setupMainUi(this);  // Setup the main Ui
    setupConnections(); // Setup signal-slot
}

// Setup the main layout of the setting page
void ISettingPage::setupMainUi(QWidget *widget) {
    // Set object name and properties
    setObjectName("ISettingPage");
    setContentsMargins(80, 80, 80, 80);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    // Create main layout
    m_mainLayout = new QHBoxLayout(widget);

    // Create center widget
    m_centerWidget = new QWidget;
    m_mainLayout->addWidget(m_centerWidget);

    // Setup center widget layout and components
    setupCenterWidget(m_centerWidget);
}

void ISettingPage::setupCenterWidget(QWidget *widget) {
    widget->setObjectName("settingCenterWidget");
    widget->setAutoFillBackground(true);

    StyleManager::applyPalette(widget);

    auto centerLayout = new QHBoxLayout(widget);

    m_sideArea = new QWidget(widget);
    m_sideArea->setFixedWidth(120);

    auto line = new QFrame;
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);

    auto m_right = new QGridLayout;

    centerLayout->addWidget(m_sideArea);
    centerLayout->addWidget(line);
    centerLayout->addLayout(m_right);

    setupSideWidget(m_sideArea);
    setupRightLayout(m_right);
}

void ISettingPage::setupRightLayout(QGridLayout *right) {
    right->addWidget(new QLabel("Account"), 0, 0);

    m_closeButton = new QPushButton("x");
    m_closeButton->setFixedSize(QSize(30, 30));
    m_closeButton->setObjectName("smallButton");
    right->addWidget(m_closeButton, 0, 1);

    auto line1 = new QFrame();
    line1->setFrameShape(QFrame::HLine);
    line1->setFrameShadow(QFrame::Sunken);

    m_settingLayout = new QStackedLayout;

    right->addWidget(line1, 1, 0, 1, 2);
    right->addLayout(m_settingLayout, 2, 0, 1, 2);

    setupSettingsLayout(m_settingLayout);
}

void ISettingPage::setupSettingsLayout(QStackedLayout *widget) {

    m_accountWidget = new QWidget;
    widget->addWidget(m_accountWidget);

    m_ollamaWidget = new QWidget;
    widget->addWidget(m_ollamaWidget);

    m_promptWidget = new QWidget;
    widget->addWidget(m_promptWidget);

    setupAccountWidget(m_accountWidget); // Setup the setting area
    setupOllamaWidget(m_ollamaWidget);
    setupPromptWidget(m_promptWidget);
}

// Setup the top area of the setting page
void ISettingPage::setupSideWidget(QWidget *widget) {
    auto layout = new QVBoxLayout(widget);
    layout->setContentsMargins(5, 8, 5, 10);
    layout->setAlignment(Qt::AlignTop);

    m_accountButton = new QPushButton(QIcon("://icons/account.svg"), "Account");
    m_accountButton->setObjectName("bigButton");
    m_ollamaButton = new QPushButton(QIcon("://images/ollama.png"), "Ollama");
    m_ollamaButton->setObjectName("bigButton");
    m_promptButton = new QPushButton(QIcon("://icons/prompt.svg"), "Prompt");
    m_promptButton->setObjectName("bigButton");

    layout->addWidget(new QLabel("Settings"));
    layout->addWidget(m_accountButton);
    layout->addWidget(m_ollamaButton);
    layout->addWidget(m_promptButton);
}

QGroupBox *ISettingPage::addSettingGroupBox(const QString &key,
                                            const QString &value,
                                            const QString &configKey) {
    auto groupBox = new QGroupBox(key);
    auto lineEdit = new QLineEdit(value);
    auto editButton = new QPushButton("Edit");

    lineEdit->setDisabled(true);
    lineEdit->setFrame(false);
    editButton->setObjectName("smallButton");

    groupBox->setStyleSheet(
        "QGroupBox { border: 0px; background-color: white; }");
    groupBox->setLayout(new QHBoxLayout);
    groupBox->layout()->setContentsMargins(11, 21, 11, 21);

    groupBox->layout()->addWidget(lineEdit);
    groupBox->layout()->addWidget(editButton);

    connect(editButton, &QPushButton::clicked, this,
            [lineEdit, editButton, configKey]() {
        lineEdit->setEnabled(!lineEdit->isEnabled());
        editButton->setText(lineEdit->isEnabled() ? "Done" : "Edit");
        if (!configKey.isEmpty() && editButton->text() == "Done") {
            ConfigManager::instance().setConfig(configKey, lineEdit->text());
        }
    });

    return groupBox;
}

// Setup the setting area of the setting page
void ISettingPage::setupOllamaWidget(QWidget *ollama) {
    auto layout = new QVBoxLayout(ollama);
    layout->setSpacing(10);
    layout->setAlignment(Qt::AlignTop);

    layout->addWidget(addSettingGroupBox(
        "Model files directory",
        ConfigManager::instance().config("modeldir").toString(), "modeldir"));
    layout->addWidget(
        addSettingGroupBox("Ollama port", "localhost:11434", "ollamaport"));
    layout->addWidget(
        addSettingGroupBox("Ollama address", "localhost", "ollamadomain"));
}

// Setup the setting area of the setting page
void ISettingPage::setupPromptWidget(QWidget *widget) {
    auto layout = new QVBoxLayout(widget);
    layout->setSpacing(10);
    layout->setAlignment(Qt::AlignTop);

    layout->addWidget(
        addSettingGroupBox("Prompt", "Reply with English", "prompt"));
}

// Setup the setting area of the setting page
void ISettingPage::setupAccountWidget(QWidget *account) {
    auto layout = new QVBoxLayout(account);
    layout->setSpacing(10);
    layout->setAlignment(Qt::AlignTop);

    QPixmap avatar(ConfigManager::instance().config("avatar").toString());
    qDebug() << "ConfigManager::instance().config(avatar).toString()"
             << ConfigManager::instance().config("avatar").toString();
    m_avatarButton = new QPushButton(this);
    m_avatarButton->setFixedSize(60, 60);
    m_avatarButton->setStyleSheet(
        QString("border: 2px solid black; border-radius: %1px;")
            .arg(m_avatarButton->width() / 2));
    m_avatarButton->setIcon(QIcon(StyleManager::roundedPixmap(avatar)));
    m_avatarButton->setIconSize(m_avatarButton->size());

    QHBoxLayout *lay = new QHBoxLayout;
    lay->addWidget(m_avatarButton);
    lay->addWidget(addSettingGroupBox("User name", "QOllama", "username"));

    layout->addLayout(lay);
}

// Setup signal-slot connections
void ISettingPage::setupConnections() {
    connect(m_avatarButton, &QPushButton::clicked, this,
            &ISettingPage::toChangeAvatar); // Change avatar button clicked

    connect(m_accountButton, &QPushButton::clicked, this,
            [this]() { m_settingLayout->setCurrentWidget(m_accountWidget); });
    connect(m_ollamaButton, &QPushButton::clicked, this,
            [this]() { m_settingLayout->setCurrentWidget(m_ollamaWidget); });
    connect(m_promptButton, &QPushButton::clicked, this,
            [this]() { m_settingLayout->setCurrentWidget(m_promptWidget); });
    connect(m_closeButton, &QPushButton::clicked, this, &QWidget::close);
}

// Slot to change avatar
void ISettingPage::toChangeAvatar() {
    QString fileName = QFileDialog::getOpenFileName(
        this, "Select Avatar", "", "Image Files (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty()) {
        QPixmap newAvatar(fileName);
        if (newAvatar.isNull()) {
            QMessageBox::warning(this, "Error", "Failed to load the image.");
            return;
        }
        newAvatar = StyleManager::roundedPixmap(newAvatar);

        m_avatarButton->setIcon(QIcon(newAvatar));
        ConfigManager::instance().setConfig("avatar", fileName);

        emit ConfigManager::instance().onAvatarChanged();
    }
}

void ISettingPage::showEvent(QShowEvent *event) {
    QDialog::showEvent(event);
    QWidget *parent = qobject_cast<QWidget *>(this->parent());

    if (parent) {
        // Get the global screen coordinates of the parent window
        QPoint globalPos = parent->mapToGlobal(QPoint(0, 0));

        // Parent window's width and height
        int parentWidth = parent->width();
        int parentHeight = parent->height();

        // Width and height of ISettingPage (same as parent window's size)
        int width = parentWidth * 1;
        int height = parentHeight * 1;

        // Calculate the top-left coordinates of ISettingPage to center it in the
        // parent window
        int x = globalPos.x() + (parentWidth - width) / 2;
        int y = globalPos.y() + (parentHeight - height) / 2;

#ifdef Q_OS_WIN
        // Get the system title bar height
        int titleBarHeight = GetSystemMetrics(SM_CYCAPTION);
        y -= titleBarHeight;
        height += titleBarHeight;
#endif

        // Set the position and size of ISettingPage
        setGeometry(x, y, width, height);
    }
}

void ISettingPage::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Set gray semi-transparent background
    QColor backgroundColor(128, 128, 128,
                           128); // RGB(128, 128, 128) is gray, the last parameter
        // 128 is the transparency (range 0-255)
    painter.fillRect(this->rect(), backgroundColor);
}
