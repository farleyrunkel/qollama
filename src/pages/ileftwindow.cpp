#include "ileftwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QFile>

ILeftWindow::ILeftWindow(QWidget *parent) : IWidget(parent) {
    setupUi();
}

void ILeftWindow::setupUi() {
    setMaximumSize(QSize(200, 16777215));
    setObjectName("leftWindow");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(2);

    setupTitleBar(mainLayout);
    setupButtons(mainLayout);
    setupHistoryList(mainLayout);
    setupSettingButton(mainLayout);
}

void ILeftWindow::setupTitleBar(QVBoxLayout *layout) {
    QWidget *titleBar = createButtonContainer(this, "leftTitleBar", ":/icon/sidebar-left.svg", QSize(30, 30), layout);
    QHBoxLayout *titleBarLayout = qobject_cast<QHBoxLayout*>(titleBar->layout());

    m_expandButton = createButton(titleBar, "smallButton", ":/icon/sidebar-left.svg", QSize(30, 30));
    titleBarLayout->addWidget(m_expandButton);

    QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    titleBarLayout->addItem(spacer);

    QPushButton *m_newChatButton = createButton(titleBar, "smallButton", ":/icon/create-new.svg", QSize(30, 30));
    titleBarLayout->addWidget(m_newChatButton);

    // Set tool tips
    m_expandButton->setToolTip(tr("Expand"));
    m_newChatButton->setToolTip(tr("Llama3"));
}

void ILeftWindow::setupButtons(QVBoxLayout *layout) {
    QFont buttonFont;
    buttonFont.setFamilies({QString::fromUtf8("Microsoft YaHei UI")});
    buttonFont.setPointSize(10);
    buttonFont.setWeight(QFont::Medium);

    m_modelButton = createOverlayButton(this, "newChatButton", buttonFont, QSize(0, 34));
    layout->addWidget(m_modelButton);
    m_modelButton->setText(tr("Llama3"));

    m_exploreButton = createButton(this, "exploreButton", ":/icon/sparkles.png", QSize(0, 34), false);
    m_exploreButton->setFont(buttonFont);
    layout->addWidget(m_exploreButton);
    m_exploreButton->setText(tr("Explore"));
}

void ILeftWindow::setupHistoryList(QVBoxLayout *layout) {
    m_historyList = new IHistoryList(this);
    m_historyList->setObjectName("historyList");
    m_historyList->setFocusPolicy(Qt::NoFocus);
    m_historyList->setFrameShape(QFrame::NoFrame);
    m_historyList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_historyList->setProperty("showDropIndicator", QVariant(false));
    m_historyList->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    layout->addWidget(m_historyList);
}

void ILeftWindow::setupSettingButton(QVBoxLayout *layout) {
    QFont buttonFont;
    buttonFont.setFamilies({QString::fromUtf8("Microsoft YaHei UI")});
    buttonFont.setPointSize(10);
    buttonFont.setWeight(QFont::Medium);

    m_settingButton = createButton(this, "settingButton", ":/icon/gear.svg", QSize(0, 40), false);
    m_settingButton->setFont(buttonFont);
    m_settingButton->setIconSize(QSize(20, 20));
    layout->addWidget(m_settingButton);
    m_settingButton->setText(tr("Settings"));
}

QWidget* ILeftWindow::createButtonContainer(QWidget *parent, const QString &objectName, const QString &iconPath, const QSize &size, QVBoxLayout *layout) {
    QWidget *container = new QWidget(parent);
    container->setObjectName(objectName);
    QHBoxLayout *containerLayout = new QHBoxLayout(container);
    containerLayout->setSpacing(0);
    containerLayout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(container);
    return container;
}

QPushButton* ILeftWindow::createButton(QWidget *parent, const QString &objectName, const QString &iconPath, const QSize &size, bool isFixedSize) {
    QPushButton *button = new QPushButton(parent);
    button->setObjectName(objectName);
    button->setIcon(QIcon(iconPath));
    if (isFixedSize) {
        button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        button->setMinimumSize(size);
        button->setMaximumSize(size);
    } else {
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        button->setMinimumSize(size);
        button->setMaximumSize(QSize(16777215, size.height()));
    }
    return button;
}

IOverlayButton* ILeftWindow::createOverlayButton(QWidget *parent, const QString &objectName, const QFont &font, const QSize &size) {
    IOverlayButton *button = new IOverlayButton(parent);
    button->setObjectName(objectName);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    button->setMinimumSize(size);
    button->setMaximumSize(QSize(16777215, size.height()));
    button->setFont(font);
    button->setFocusPolicy(Qt::NoFocus);
    button->setLayoutDirection(Qt::LeftToRight);
    return button;
}

QPushButton* ILeftWindow::settingButton() const {
    return m_settingButton;
}

QPushButton* ILeftWindow::expandButton() const {
    return m_expandButton;
}

IOverlayButton* ILeftWindow::newChatButton() const {
    return m_modelButton;
}

QPushButton* ILeftWindow::exploreButton() const {
    return m_exploreButton;
}
