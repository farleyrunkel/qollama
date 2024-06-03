#include "IMarketPage.h"
#include "IHPushCard.h"
#include "ILineEdit.h"

IMarketPage::IMarketPage(QWidget *parent) : QScrollArea(parent)
{
    qDebug() << "IMarketPage constructor called";

    setWidgetResizable(true);
    setAlignment(Qt::AlignTop);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setContentsMargins(0, 0, 0, 0);

    containerWidget = new QWidget(this);
    containerWidget->setObjectName("marketContainerWidget");
    contentLayout = new QVBoxLayout(containerWidget);
    contentLayout->setContentsMargins(60, 0, 40, 0);
    contentLayout->setSpacing(15);
    containerWidget->setLayout(contentLayout);
    containerWidget->setContentsMargins(0, 0, 0, 0);
    setWidget(containerWidget);

    mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
    mainLayout->setSpacing(0);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->setContentsMargins(60, 0, 60, 0);

    setupTitle();
    setupSearchLine();
    setupNavigator();
    setupTopSearchArea();
    setupCategories();
}

void IMarketPage::setupTitle()
{
    qDebug() << "Setting up title";

    auto titleLabel = new QLabel;
    titleLabel->setWordWrap(true);
    titleLabel->setText(
        "<p style='text-align: center; font-size: 48px; font-weight: bold; color: black;'>GPTs</p>"
        "<p style='text-align: center; font-size: 12px; color: gray;'>Explore and create a customized version of ChatGPT that integrates commands, additional knowledge, and any combination of skills.</p>");
    titleWidget = titleLabel;
    contentLayout->addWidget(titleWidget);
}

void IMarketPage::setupSearchLine()
{
    qDebug() << "Setting up search line";

    searchLineEdit = createSearchLineEdit();
    contentLayout->addWidget(searchLineEdit);
}

ILineEdit* IMarketPage::createSearchLineEdit()
{
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

void IMarketPage::setupNavigator()
{
    qDebug() << "Setting up navigator";

    m_navigator = new INavigetrorBar;

    contentLayout->addWidget(m_navigator);

    connect(m_navigator, &INavigetrorBar::buttonClicked, [this](QPushButton *button) {
        qDebug() << "INavigetrorBar button clicked:" << button->text();
        m_topNavigator->showUnderline(m_topNavigator->getUnderlineLabel(button->text()));
        navigateToCategory(button->text());
    });
}


void IMarketPage::setupTopSearchArea()
{
    qDebug() << "Setting up top search area";

    topSearchArea = new QWidget;

    auto topSearchAreaLayout = new QVBoxLayout;
    topSearchArea->setLayout(topSearchAreaLayout);
    topSearchArea->setStyleSheet("background-color: white;");

    auto lineEdit = createSearchLineEdit();
    topSearchAreaLayout->addWidget(lineEdit);
    topSearchAreaLayout->setContentsMargins(0, 0, 0, 15);
    topSearchAreaLayout->setSpacing(contentLayout->spacing());
    m_topNavigator = new INavigetrorBar;

    topSearchAreaLayout->addWidget(m_topNavigator);

    mainLayout->addWidget(topSearchArea);
    mainLayout->addStretch(1);
    topSearchArea->hide();

    connect(m_topNavigator, &INavigetrorBar::buttonClicked, this, [this](QPushButton *button) {
        qDebug() << "INavigetrorBar button clicked:" << button->text();
        m_navigator->showUnderline(m_navigator->getUnderlineLabel(button->text()));
        navigateToCategory(button->text());
    });
}

QWidget* IMarketPage::createCategoryCard(const QString &categoryName)
{
    qDebug() << "Creating new category card for:" << categoryName;

    auto categoryWidget = new QWidget(containerWidget);

    categoryMap[categoryName] = categoryWidget;

    auto categoryLayout = new QGridLayout(categoryWidget);
    categoryWidget->setLayout(categoryLayout);
    categoryLayout->setAlignment(Qt::AlignLeft);
    categoryLayout->addItem(new QSpacerItem(0, 0), 0, 1);
    categoryLayout->setSpacing(10);

    return categoryWidget;
}

void IMarketPage::addCategory(const QString &categoryName)
{
    qDebug() << "Adding category:" << categoryName;

    auto categoryLabel = new QLabel;
    categoryLabel->setText(QString("<p style='text-align: left; font-size: 20px; font-weight: bold; color: black;'>%1</p>").arg(categoryName));
    contentLayout->addWidget(categoryLabel);

    auto categoryWidget = createCategoryCard(categoryName);
    contentLayout->addWidget(categoryWidget);

    for (int i = 0;i < 5;  ++i)
    {
        qDebug() << "Adding IHPushCard to category:" << categoryName << "index:" << i;
        categoryWidget->layout()->addWidget(new IHPushCard(categoryWidget->layout()->count()));
    }

    m_navigator->addButton(categoryName);
    m_topNavigator->addButton(categoryName);
}

void IMarketPage::navigateToCategory(const QString &categoryName)
{
    qDebug() << "Navigating to category:" << categoryName;

    auto categoryWidget = categoryMap.value(categoryName);
    if (categoryWidget) {
        qDebug() << "Scrolling to category:" << categoryName;
        verticalScrollBar()->setValue(categoryWidget->geometry().top() - m_topNavigator->height() - 80);
    }
}

void IMarketPage::setupCategories()
{
    qDebug() << "Setting up categories";

    addCategory("Recommend");
    addCategory("Write");
    addCategory("Productivity");
    addCategory("Research");
    addCategory("Education");
    addCategory("Life");
    addCategory("Program");
}

void IMarketPage::scrollContentsBy(int dx, int dy)
{
    QScrollArea::scrollContentsBy(dx, dy);
    qDebug() << "Scrolling contents by dx:" << dx << "dy:" << dy;
    if (m_navigator && m_topNavigator) {
        if (verticalScrollBar()->value() >= (m_navigator->y() - m_topNavigator->y())) {
            qDebug() << "Showing top search area";
            topSearchArea->show();
        } else {
            qDebug() << "Hiding top search area";
            topSearchArea->hide();
        }
    }
}

void IMarketPage::resizeEvent(QResizeEvent *event)
{
    QScrollArea::resizeEvent(event);
    containerWidget->setFixedWidth( this->width() - 19);
}
