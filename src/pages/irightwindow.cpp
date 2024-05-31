#include "irightwindow.h"
#include <QLabel>

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

    // 创建左侧和右侧的容器Widget
    QWidget* leftContainer = new QWidget;
    leftContainer->setLayout(leftWidget);
    leftContainer->setMinimumWidth(50);
    leftContainer->setMaximumWidth(50);

    QWidget* rightContainer = new QWidget;
    rightContainer->setLayout(rightWidget);
    rightContainer->setMinimumWidth(50);
    rightContainer->setMaximumWidth(50);

    // 将容器Widget添加到主布局
    mainLayout->addWidget(leftContainer);
    mainLayout->addWidget(m_pages);
    mainLayout->addWidget(rightContainer);

    // 初始化按钮并添加到左侧和右侧
    expandButton = new QPushButton;
    expandButton->setIcon(QIcon("://icon/farley.jpg"));
    setLeftWidget(expandButton);

    userButton = new QPushButton;
    userButton->setIcon(QIcon("://icon/farley.jpg"));
    setRightWidget(userButton);
}

void IRightWindow::setLeftWidget(QWidget* widget)
{
    leftWidget->addWidget(widget);
}

void IRightWindow::setRightWidget(QWidget* widget)
{
    rightWidget->addWidget(widget);
}
