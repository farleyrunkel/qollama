#include "imarketpage.h"
#include "ihpushcard.h"
#include "ilineedit.h"
#include <QStackedLayout>
#include <QStackedWidget>
#include "signalhub.h"

/**
 * @brief IMarketPage constructor
 *
 * @param parent Parent widget
 */
IMarketPage::IMarketPage(QWidget *parent) : QWidget(parent) {
    setupMainLayout();
    setupTopArea();
    setupScrollArea();
    setupConnections();
}

/**
 * @brief Set up the main layout of the market page
 */
void IMarketPage::setupMainLayout() {
    setObjectName("IMarketPage");
    setContentsMargins(0, 0, 0, 0);

    m_mainLayout = new QVBoxLayout(this);
    setLayout(m_mainLayout);

    m_topArea = new QWidget(this);
    m_topArea->setFixedHeight(35);

    m_scrollArea = new IScrollArea(this);

    m_mainLayout->addWidget(m_topArea);
    m_mainLayout->addWidget(m_scrollArea);
}

/**
 * @brief Set up the top area of the market page
 */
void IMarketPage::setupTopArea() {
    auto topAreaLayout = new QHBoxLayout(m_topArea);
    topAreaLayout->setContentsMargins(0, 0, 0, 0);

    m_expandButton = createButton("://icon/sidebar-left.svg");
    m_newChatButton = createButton(":/icon/create-new.svg");
    m_userButton = createButton("://icon.png");

    m_expandButton->hide();
    m_newChatButton->hide();
    m_userButton->hide();

    m_topStack = new QStackedWidget;
    m_topSearchLine = createSearchLineEdit();
    m_topSpace = new QWidget;
    m_topStack->addWidget(m_topSearchLine);
    m_topStack->addWidget(m_topSpace);
    m_topStack->setCurrentWidget(m_topSpace);

    topAreaLayout->addWidget(m_expandButton);
    topAreaLayout->addWidget(m_newChatButton);
    topAreaLayout->addWidget(m_topStack);
    topAreaLayout->addWidget(m_userButton);
}

/**
 * @brief Set up the scroll area of the market page
 */
void IMarketPage::setupScrollArea() {
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

    setupTopNavigator();
    setupTitleLabel();
    setupSearchLine();
    setupNavigator();
    setupCategories();
}

/**
 * @brief Set up connections for signals and slots
 */
void IMarketPage::setupConnections() {
    connect(m_topNavigator, &INavigetrorBar::buttonClicked, this, [this](QPushButton *button) {
        qDebug() << "INavigetrorBar button clicked:" << button->text();
        m_navigator->showUnderline(m_navigator->getUnderlineLabel(button->text()));
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

    connect(m_expandButton, &QPushButton::clicked, &SignalHub::instance(), &SignalHub::onExpandButtonClicked);
    connect(&SignalHub::instance(), &SignalHub::onSideAreaHidden, m_expandButton, &QPushButton::setVisible);
    connect(&SignalHub::instance(), &SignalHub::onSideAreaHidden, m_newChatButton, &QPushButton::setVisible);
    connect(&SignalHub::instance(), &SignalHub::onSideAreaHidden, m_userButton, &QPushButton::setVisible);
}

/**
 * @brief Set up the top navigator bar
 */
void IMarketPage::setupTopNavigator() {
    m_topNavigator = new INavigetrorBar(this);
    m_scrollLayout->addWidget(m_topNavigator);
    m_scrollLayout->setAlignment(Qt::AlignTop);
    m_topNavigator->hide();
}

/**
 * @brief Set up the title label
 */
void IMarketPage::setupTitleLabel() {
    qDebug() << "Setting up title";

    auto titleWidget = new QLabel;
    titleWidget->setWordWrap(true);
    titleWidget->setText(
        "<p style='text-align: center; font-size: 48px; font-weight: bold; color: black;'>GPTs</p>"
        "<p style='text-align: center; font-size: 12px; color: gray;'>Explore and create a customized version of ChatGPT that integrates commands, additional knowledge, and any combination of skills.</p>");

    m_scrollWidgetLayout->addWidget(titleWidget);
}

/**
 * @brief Set up the search line edit
 */
void IMarketPage::setupSearchLine() {
    qDebug() << "Setting up search line";

    searchLineEdit = createSearchLineEdit();
    searchLineEdit->setFixedHeight(40);
    m_scrollWidgetLayout->addWidget(searchLineEdit);
}

/**
 * @brief Create a search line edit widget
 *
 * @return ILineEdit* Pointer to the created search line edit
 */
ILineEdit* IMarketPage::createSearchLineEdit() {
    auto lineEdit = new ILineEdit;
    lineEdit->setObjectName("marketPageSearchLine");
    lineEdit->setPlaceholderText("Search GPT");
    lineEdit->rightButton()->hide();
    lineEdit->leftButton()->setFlat(true);
    QIcon searchIcon;
    searchIcon.addPixmap(QPixmap("://icon/search.svg"), QIcon::Disabled, QIcon::On);
    lineEdit->leftButton()->setIcon(searchIcon);
    lineEdit->leftButton()->setDisabled(true);

    return lineEdit;
}

/**
 * @brief Set up the navigator bar
 */
void IMarketPage::setupNavigator() {
    qDebug() << "Setting up navigator";

    m_navigator = new INavigetrorBar;
    m_scrollWidgetLayout->addWidget(m_navigator);

    connect(m_navigator, &INavigetrorBar::buttonClicked, this, [this](QPushButton *button) {
        qDebug() << "INavigetrorBar button clicked:" << button->text();
        m_topNavigator->showUnderline(m_topNavigator->getUnderlineLabel(button->text()));
        navigateToCategory(button->text());
    });
}

/**
 * @brief Create a category card widget
 *
 * @param categoryName Name of the category
 * @return QWidget* Pointer to the created category card widget
 */
QWidget* IMarketPage::createCategoryCard(const QString &categoryName) {
    qDebug() << "Creating new category card for:" << categoryName;

    auto categoryWidget = new QWidget(m_scrollWidget);
    categoryMap[categoryName] = categoryWidget;

    auto categoryLayout = new QGridLayout(categoryWidget);
    categoryWidget->setLayout(categoryLayout);
    categoryLayout->setAlignment(Qt::AlignLeft);
    categoryLayout->addItem(new QSpacerItem(0, 0), 0, 1);
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
    categoryLabel->setText(QString("<p style='text-align: left; font-size: 20px; font-weight: bold; color: black;'>%1</p>").arg(categoryName));
    m_scrollWidgetLayout->addWidget(categoryLabel);

    auto categoryWidget = createCategoryCard(categoryName);
    m_scrollWidgetLayout->addWidget(categoryWidget);

    for (int i = 0; i < 5; ++i) {
        qDebug() << "Adding IHPushCard to category:" << categoryName << "index:" << i;
        categoryWidget->layout()->addWidget(new IHPushCard(categoryWidget->layout()->count()));
    }

    m_navigator->addButton(categoryName);
    m_topNavigator->addButton(categoryName);
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
        m_scrollArea->verticalScrollBar()->setValue(categoryWidget->geometry().top() - labelHeight - m_topNavigator->height());
    }
}

/**
 * @brief Set up all categories
 */
void IMarketPage::setupCategories() {
    qDebug() << "Setting up categories";

    addCategory("Recommend");
    addCategory("Write");
    addCategory("Research");
    addCategory("Education");
    addCategory("Life");
    addCategory("Program");

    m_navigator->showUnderline(m_navigator->getUnderlineLabel("Recommend"));
    m_topNavigator->showUnderline(m_topNavigator->getUnderlineLabel("Recommend"));
}

/**
 * @brief Create a button with an icon
 *
 * @param iconPath Path to the icon image
 * @return QPushButton* Pointer to the created button
 */
QPushButton* IMarketPage::createButton(const QString& iconPath) {
    auto button = new QPushButton;
    button->setIcon(QIcon(iconPath));
    button->setFixedSize(QSize(30, 30));
    button->setObjectName("smallButton");
    return button;
}

/**
 * @brief Get the expand button
 *
 * @return QPushButton* Pointer to the expand button
 */
QPushButton* IMarketPage::expandButton() const {
    return m_expandButton;
}
