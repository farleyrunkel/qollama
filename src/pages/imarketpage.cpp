#include "imarketpage.h"
#include "configmanager.h"
#include "dataloader.h"
#include "ihpushcard.h"
#include "ilineedit.h"
#include "signalhub.h"
#include "stylemanager.h"
#include <QDialog>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonParseError>
#include <QStackedLayout>
#include <QStackedWidget>

/**
 * @brief IMarketPage constructor
 *
 * @param parent Parent widget
 */
IMarketPage::IMarketPage(QWidget *parent) : IWidget(parent) {

    setupMainUi(this);
    setupConnections();
}

/**
 * @brief Set up the main layout of the market page
 */
void IMarketPage::setupMainUi(QWidget *widget) {
    setObjectName("IMarketPage");

    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setSpacing(2);
    m_mainLayout->setAlignment(Qt::AlignTop);

    auto topBar = new QWidget;
    auto scrollArea = new IScrollArea;

    m_mainLayout->addWidget(topBar);
    m_mainLayout->addWidget(scrollArea);

    setupTopBar(topBar);
    setupScrollArea(scrollArea);
}

/**
 * @brief Set up the top area of the market page
 */
void IMarketPage::setupTopBar(QWidget *widget) {
    widget->setFixedHeight(ConfigManager::instance()
                               .config("topBar")
                               .toJsonObject()
                               .value("height")
                               .toInt());
    auto layout = new QHBoxLayout(widget);
    layout->setAlignment(Qt::AlignVCenter);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    m_expandButton = new QPushButton(QIcon("://icons/sidebar-left.svg"), "");
    m_expandButton->setObjectName("smallButton");

    m_newChatButton = new QPushButton(QIcon(":/icons/create-new.svg"), "");
    m_newChatButton->setObjectName("smallButton");

    m_expandButton->hide();
    m_newChatButton->hide();

    QPixmap avatar(ConfigManager::instance().config("avatar").toString());
    m_userButton =
        new QPushButton(QIcon(StyleManager::roundedPixmap(avatar)), "");
    m_userButton->setObjectName("smallButton");

    m_topStack = new QStackedLayout;
    m_topSearchLine = createSearchLineEdit();
    m_topSpace = new QWidget;

    m_topStack->addWidget(m_topSearchLine);
    m_topStack->addWidget(m_topSpace);
    m_topStack->setCurrentWidget(m_topSpace);

    layout->addWidget(m_expandButton);
    layout->addWidget(m_newChatButton);
    layout->addLayout(m_topStack);
    layout->addWidget(m_userButton);
}

/**
 * @brief Set up the scroll area of the market page
 */
void IMarketPage::setupScrollArea(QWidget *widget) {

    m_scrollArea = qobject_cast<IScrollArea *>(widget);

    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setAlignment(Qt::AlignTop);
    m_scrollArea->setFrameShape(QFrame::NoFrame);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_scrollArea->setStyleSheet("background-color: white;");

    m_scrollLayout = new QVBoxLayout;
    m_scrollArea->setLayout(m_scrollLayout);

    int margin = 20;
    m_scrollLayout->setContentsMargins(margin, 0, margin, 0);

    m_scrollWidget = new QWidget;
    m_scrollArea->setWidget(m_scrollWidget);
    m_scrollWidget->setContentsMargins(0, 0, 0, 0);
    m_scrollWidgetLayout = new QVBoxLayout(m_scrollWidget);
    m_scrollWidget->setLayout(m_scrollWidgetLayout);
    m_scrollWidgetLayout->setContentsMargins(margin, 0, margin, 0);

    setupTopNavigator(m_scrollLayout);
    setupTitleLabel(m_scrollWidgetLayout);
    setupSearchLine(m_scrollWidgetLayout);
    setupNavigator(m_scrollWidgetLayout);
}

/**
 * @brief Set up the top navigator bar
 */
void IMarketPage::setupTopNavigator(QLayout *layout) {
    m_topNavigator = new INavigetrorBar(this);
    m_topNavigator->hide();
    layout->addWidget(m_topNavigator);
    layout->setAlignment(Qt::AlignTop);
}

/**
 * @brief Set up the title label
 */
void IMarketPage::setupTitleLabel(QLayout *layout) {
    qDebug() << "Setting up title";

    auto titleWidget = new QLabel;
    titleWidget->setWordWrap(true);
    titleWidget->setText(
        "<p style='text-align: center; font-size: 32px; font-weight: bold; "
        "color: black; margin-bottom: 1px; '>Prompts</p>"
        "<p style='text-align: center; font-size: 10px; color: gray;margin-top: "
        "1px;  '>Explore "
        "and create a customized version of prompts.</p>");

    layout->addWidget(titleWidget);
}

/**
 * @brief Set up the search line edit
 */
void IMarketPage::setupSearchLine(QLayout *layout) {
    qDebug() << "Setting up search line";

    searchLineEdit = createSearchLineEdit();
    searchLineEdit->setFixedHeight(40);
    layout->addWidget(searchLineEdit);
}

/**
 * @brief Create a search line edit widget
 *
 * @return ILineEdit* Pointer to the created search line edit
 */
ILineEdit *IMarketPage::createSearchLineEdit() {
    auto lineEdit = new ILineEdit;
    lineEdit->setObjectName("marketPageSearchLine");
    lineEdit->setPlaceholderText("Search prompts");
    lineEdit->rightButton()->hide();
    lineEdit->leftButton()->setFlat(true);
    QIcon searchIcon;
    searchIcon.addPixmap(QPixmap("://icons/search.svg"), QIcon::Disabled,
                         QIcon::On);
    lineEdit->leftButton()->setIcon(searchIcon);
    lineEdit->leftButton()->setDisabled(true);

    return lineEdit;
}

/**
 * @brief Set up the navigator bar
 */
void IMarketPage::setupNavigator(QLayout *layout) {
    qDebug() << "Setting up navigator";

    m_navigator = new INavigetrorBar;
    layout->addWidget(m_navigator);

    connect(m_navigator, &INavigetrorBar::buttonClicked, this,
            [this](QPushButton *button) {
                qDebug() << "INavigetrorBar button clicked:" << button->text();
        m_topNavigator->showUnderline(
                    m_topNavigator->getUnderlineLabel(button->text()));
                navigateToCategory(button->text());
    });
}

/**
 * @brief Create a category card widget
 *
 * @param categoryName Name of the category
 * @return QWidget* Pointer to the created category card widget
 */
QWidget *IMarketPage::createCategoryCard(const QString &categoryName) {
    qDebug() << "Creating new category card for:" << categoryName;

    auto categoryWidget = new QWidget(m_scrollWidget);
    categoryMap[categoryName] = categoryWidget;

    auto categoryLayout = new QGridLayout(categoryWidget);
    categoryWidget->setLayout(categoryLayout);
    categoryLayout->setAlignment(Qt::AlignLeft);
    categoryLayout->addItem(new QSpacerItem(0, 0), 0, 0);
    categoryLayout->setSpacing(10);

    return categoryWidget;
}

/**
 * @brief Add a new category
 *
 * @param categoryName Name of the category
 */
void IMarketPage::addCategory(const QString &categoryName) {
    qDebug() << "Adding category:" << categoryName;

    auto categoryLabel = new QLabel;
    categoryLabel->setText(QString("<p style='text-align: left; font-size: 20px; "
                                   "font-weight: bold; color: black;'>%1</p>")
                               .arg(categoryName));
    m_scrollWidgetLayout->addWidget(categoryLabel);

    auto categoryWidget = createCategoryCard(categoryName);

    m_categories[categoryName] = categoryWidget;

    m_scrollWidgetLayout->addWidget(categoryWidget);

    m_navigator->addButton(categoryName);
    m_topNavigator->addButton(categoryName);
}

void IMarketPage::addCategoryItem(const QString &categoryName,
                                  IHPushCard *item) {
    qDebug() << "Adding category item:" << categoryName;

    // Check if the category already exists in m_categories
    if (!m_categories.contains(categoryName)) {
        createCategoryCard(categoryName);
    }

    auto categoryWidget = m_categories[categoryName];
    item->setNumber(categoryWidget->layout()->count());

    categoryWidget->layout()->addWidget(item);
}

/**
 * @brief Navigate to a specific category
 *
 * @param categoryName Name of the category to navigate to
 */
void IMarketPage::navigateToCategory(const QString &categoryName) {
    qDebug() << "Navigating to category:" << categoryName;

    auto categoryWidget = categoryMap.value(categoryName);
    if (categoryWidget) {
        qDebug() << "Scrolling to category:" << categoryName;
        int labelHeight = 38;
        m_scrollArea->verticalScrollBar()->setValue(
            categoryWidget->geometry().top() - labelHeight -
            m_topNavigator->height());
    }
}

/**
 * @brief Set up all categories
 */
void IMarketPage::load() {
    qDebug() << "Setting up categories";

    addCategory("Top");

    auto prompts = DataLoader::instance().prompts();

    // Iterate through each JSON file
    foreach (const auto &prompt, prompts) {

        auto item = new IHPushCard;

        QString name = prompt.title;
        QString intro = prompt.description;
        QString content = prompt.prompt;

        QString category = "Top";
        item->setNumber(m_categories[category]->layout()->count());
        // item->setIcon(QIcon(pixmap));
        item->setName(name);
        item->setIntro(intro);
        item->setProperty("prompt", prompt.prompt);
        if (!m_categories.contains(category)) {
            addCategory(category);
        }

        m_categories[category]->layout()->addWidget(item);
    }

    m_navigator->showUnderline(m_navigator->getUnderlineLabel("Top"));
    m_topNavigator->showUnderline(m_topNavigator->getUnderlineLabel("Top"));
}

/**
 * @brief Set up connections for signals and slots
 */
void IMarketPage::setupConnections() {
    connect(m_topNavigator, &INavigetrorBar::buttonClicked, this,
            [this](QPushButton *button) {
                qDebug() << "INavigetrorBar button clicked:" << button->text();
        m_navigator->showUnderline(
                    m_navigator->getUnderlineLabel(button->text()));
                navigateToCategory(button->text());
    });

    connect(m_scrollArea, &IScrollArea::scrolledToValue, this, [this](int y) {
        if (m_scrollLayout) {
            bool showWidgets = (y >= m_navigator->y());
            if (showWidgets) {
                m_topNavigator->show();
                m_topStack->setCurrentWidget(m_topSearchLine);
            } else {
                m_topNavigator->hide();
                m_topStack->setCurrentWidget(m_topSpace);
            }
        } else {
            qDebug() << "Layout does not exist.";
        }
    });
    connect(&ConfigManager::instance(), &ConfigManager::onAvatarChanged,
            m_userButton, [this]() {
        QPixmap avatar(
            ConfigManager::instance().config("avatar").toString());
        m_userButton->setIcon(QIcon(StyleManager::roundedPixmap(avatar)));
    });

    connect(&SignalHub::instance(), &SignalHub::onSideAreaHidden, m_expandButton,
            &QPushButton::setVisible);
    connect(&SignalHub::instance(), &SignalHub::onSideAreaHidden, m_newChatButton,
            &QPushButton::setVisible);
    connect(m_expandButton, &QPushButton::clicked, &SignalHub::instance(),
            &SignalHub::onExpandButtonClicked);
    connect(m_newChatButton, &QPushButton::clicked, &SignalHub::instance(),
            &SignalHub::onNewChatButtonClicked);
    connect(m_userButton, &QPushButton::clicked, &SignalHub::instance(),
            &SignalHub::onUserButtonClicked);
}
