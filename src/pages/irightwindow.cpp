#include "irightwindow.h"
#include <QLabel>
#include "iconfigmanager.h"

IRightWindow::IRightWindow()
{
    setupUi();
}

void IRightWindow::setupUi()
{
    mainLayout = new QHBoxLayout(this);

    leftWidget = new QVBoxLayout;
    rightWidget = new QVBoxLayout;
    m_pages = new QStackedWidget;

    leftWidget->setAlignment(Qt::AlignTop| Qt::AlignLeft);
    rightWidget->setAlignment(Qt::AlignTop | Qt::AlignRight);
    leftWidget->setContentsMargins(0, 0, 0, 0);
    rightWidget->setContentsMargins(0, 0, 0, 0);
    // 创建左侧和右侧的容器Widget
    QWidget* leftContainer = new QWidget;
    leftContainer->setLayout(leftWidget);
    leftContainer->setFixedWidth(50);

    QWidget* rightContainer = new QWidget;
    rightContainer->setLayout(rightWidget);
    rightContainer->setFixedWidth(50);

    // 将容器Widget添加到主布局
    mainLayout->addWidget(leftContainer);
    mainLayout->addWidget(m_pages);
    mainLayout->addWidget(rightContainer);

    // 初始化按钮并添加到左侧和右侧
    m_expandButton = new QPushButton;
    m_expandButton->setIcon(QIcon("://icon/sidebar-left.svg"));
    m_expandButton->setFixedSize(QSize(30, 30));
    m_expandButton->setObjectName("smallButton");
    setLeftWidget(m_expandButton);

    m_userButton = new QPushButton;
    m_userButton->setIcon(QIcon(IConfigManager::instance().getAvatar()));
    m_userButton->setFixedSize(QSize(30, 30));
    m_userButton->setObjectName("smallButton");
    setRightWidget(m_userButton);

    connect(&IConfigManager::instance(), &IConfigManager::avatarChanged, this,[&](const QPixmap& newAvatar){
        m_userButton->setIcon(QIcon(newAvatar));
        ;});
}

void IRightWindow::setLeftWidget(QWidget* widget)
{
    leftWidget->addWidget(widget);
}

void IRightWindow::setRightWidget(QWidget* widget)
{
    rightWidget->addWidget(widget);
}
