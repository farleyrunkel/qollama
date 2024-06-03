#include "IMarketPage.h"
#include "IHPushCard.h"
#include "ILineEdit.h"

IMarketPage::IMarketPage(QWidget *parent) : QScrollArea(parent)
{
    qDebug() << "IMarketPage constructor called";

    containerWidget = new QWidget(this);
    contentLayout = new QVBoxLayout(containerWidget);
    containerWidget->setLayout(contentLayout);
    contentLayout->setContentsMargins(80, 0, 80, 0);
    containerWidget->setObjectName("marketContainerWidget");

    setWidget(containerWidget);
    setWidgetResizable(true);
    setAlignment(Qt::AlignTop);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
    mainLayout->setSpacing(0);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->setContentsMargins(80, 0, 80, 0);

    setupTitle();
    setupSearchLine();
    setupNavigator();
    setupTopSearchArea();
    setupCategories();

    // Calculate the initial width difference
    initialWidthDifference = width() - containerWidget->width();
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
    qDebug() << "Creating new ILineEdit";

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
    topSearchAreaLayout->setContentsMargins(0, 0, 0, 5);

    auto lineEdit = createSearchLineEdit();
    topSearchAreaLayout->addWidget(lineEdit);


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
        verticalScrollBar()->setValue(categoryWidget->geometry().top() - topSearchArea->height() - 40);
    }
}

void IMarketPage::setupCategories()
{
    qDebug() << "Setting up categories";

    addCategory("Suggestions");
    addCategory("Write");
    addCategory("Productivity");
    addCategory("Research");
    addCategory("Education");
    addCategory("Play");
    addCategory("Life");
    addCategory("Program");
}

void IMarketPage::scrollContentsBy(int dx, int dy)
{
    QScrollArea::scrollContentsBy(dx, dy);
    qDebug() << "Scrolling contents by dx:" << dx << "dy:" << dy;
    if (m_navigator && topSearchArea) {
        if (verticalScrollBar()->value() >= (m_navigator->y() - topSearchArea->y() - this->contentsMargins().top())) {
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
    int newWidth = this->width() - initialWidthDifference;
    containerWidget->setMinimumWidth(newWidth);
    containerWidget->setMaximumWidth(newWidth);
}
