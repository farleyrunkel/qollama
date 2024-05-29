#include "imarketpage.h"
#include "ipushcard.h"

IMarketPage::IMarketPage(QWidget *parent) : QScrollArea(parent)
{
    qDebug() << "IMarketPage constructor called";

    containerWidget = new QWidget(this);
    contentLayout = new QVBoxLayout(containerWidget);
    containerWidget->setLayout(contentLayout);
    contentLayout->setContentsMargins(80, 0, 80, 0);
    containerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setStyleSheet("background-color: white; border: 1px hidden blue;");
    setWidget(containerWidget);
    setWidgetResizable(true);
    setAlignment(Qt::AlignTop);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
    mainLayout->setSpacing(0);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->setContentsMargins(80, 0, 80, 0);

    setupTitle();
    setupSearchLine();
    setupNavigator();
    setupKinds();
    setupTopSearchArea();
}

void IMarketPage::setupTopSearchArea()
{
    qDebug() << "Setting up top search area";

    topSearchArea = new QWidget;

    auto topSearchAreaLayout = new QVBoxLayout;
    topSearchArea->setLayout(topSearchAreaLayout);
    topSearchArea->setStyleSheet("background-color: white;");
    topSearchAreaLayout->setContentsMargins(0, 0, 0, 5);

    auto searchLineFrame = new QFrame;
    auto searchLineLayout = new QHBoxLayout;
    searchLineFrame->setLayout(searchLineLayout);
    searchLineFrame->setStyleSheet("border: 1px solid gray; border-radius: 15px;");
    searchLineFrame->setFixedHeight(40);
    searchLineLayout->setContentsMargins(0, 2, 10, 2);

    auto searchIconLabel = new QLabel;
    searchIconLabel->setPixmap(QIcon("://icon/search.svg").pixmap(30));
    searchIconLabel->setStyleSheet("border: 1px hidden gray; border-radius: 15px;");

    auto searchTextEdit = new QLineEdit;
    searchTextEdit->setPlaceholderText("Search GPT");
    searchTextEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    searchTextEdit->setStyleSheet("border: 1px hidden gray; border-radius: 15px;");
    searchLineLayout->addWidget(searchIconLabel);
    searchLineLayout->addWidget(searchTextEdit);

    topSearchAreaLayout->addWidget(searchLineFrame);

    auto buttonLayout = new QHBoxLayout;
    buttonLayout->setAlignment(Qt::AlignLeft);
    buttonLayout->setSpacing(15);

    for (auto a : kindButtons) {
        if (!a.first || !a.second) {
            qDebug() << "Invalid kind button or subtitle";
            continue;
        }
        auto kindButton = new QPushButton(a.first->text());
        buttonLayout->addWidget(kindButton);

        auto kindSubtitle = a.second;
        connect(kindButton, &QPushButton::clicked, this, [this, kindSubtitle]()
                {
                    if (kindSubtitle) {
                        qDebug() << "Scrolling to kind subtitle";
                        verticalScrollBar()->setValue(kindSubtitle->geometry().top() - topSearchArea->height());
                    }
                });
    }
    topSearchAreaLayout->addLayout(buttonLayout);

    mainLayout->addWidget(topSearchArea);
    mainLayout->addStretch(1);
    topSearchArea->hide();
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

    searchLineFrame = new QFrame;
    auto searchLineLayout = new QHBoxLayout;
    searchLineFrame->setLayout(searchLineLayout);
    searchLineFrame->setStyleSheet("border: 1px solid gray; border-radius: 15px;");
    searchLineFrame->setFixedHeight(40);
    searchLineLayout->setContentsMargins(0, 2, 10, 2);

    auto searchIconLabel = new QLabel;
    searchIconLabel->setPixmap(QIcon("://icon/search.svg").pixmap(30));
    searchIconLabel->setStyleSheet("border: 1px hidden gray; border-radius: 15px;");

    auto searchTextEdit = new QLineEdit;
    searchTextEdit->setPlaceholderText("Search GPT");
    searchTextEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    searchTextEdit->setStyleSheet("border: 1px hidden gray; border-radius: 15px;");
    searchLineLayout->addWidget(searchIconLabel);
    searchLineLayout->addWidget(searchTextEdit);

    contentLayout->addWidget(searchLineFrame);
}

void IMarketPage::setupNavigator()
{
    qDebug() << "Setting up navigator";

    navigatorWidget = new QWidget;
    auto navigatorLayout = new QHBoxLayout;
    navigatorWidget->setLayout(navigatorLayout);
    navigatorLayout->setAlignment(Qt::AlignLeft);
    navigatorLayout->setSpacing(15);
    contentLayout->addWidget(navigatorWidget);
}

void IMarketPage::addKind(const QString &text)
{
    qDebug() << "Adding kind:" << text;

    auto kindButton = new QPushButton(text);
    navigatorWidget->layout()->addWidget(kindButton);

    auto kindSubtitleLabel = new QLabel;
    kindSubtitleLabel->setText(QString("<p style='text-align: left; font-size: 20px; font-weight: bold; color: black;'>%1</p>").arg(text));
    contentLayout->addWidget(kindSubtitleLabel);

    auto kindItemsWidget = new QWidget;
    auto kindItemsLayout = new QGridLayout(kindItemsWidget);
    kindItemsWidget->setLayout(kindItemsLayout);
    kindItemsLayout->setAlignment(Qt::AlignLeft);
    kindItemsLayout->addItem(new QSpacerItem(0, 0), 0, 1);
    kindItemsLayout->setSpacing(10);

    for (int i = 0; i < 5; i++)
    {
        kindItemsLayout->addWidget(new IPushCard(kindItemsLayout->count()));
    }

    contentLayout->addWidget(kindItemsWidget);

    kindButtons.append(qMakePair(kindButton, kindSubtitleLabel));

    connect(kindButton, &QPushButton::clicked, this, [this, kindSubtitleLabel]()
            {
                if (kindSubtitleLabel) {
                    qDebug() << "Scrolling to kind subtitle";
                    verticalScrollBar()->setValue(kindSubtitleLabel->geometry().top() - topSearchArea->height());
                }
            });
}

void IMarketPage::setupKinds()
{
    qDebug() << "Setting up kinds";

    addKind("Suggestions");
    addKind("Write");
    addKind("Productivity");
    addKind("Research");
    addKind("Education");
    addKind("Play");
    addKind("Life");
    addKind("Program");
}

void IMarketPage::scrollContentsBy(int dx, int dy)
{
    QScrollArea::scrollContentsBy(dx, dy);
    qDebug() << "Scrolling contents by dx:" << dx << "dy:" << dy;
    if (navigatorWidget && topSearchArea) {
        if (verticalScrollBar()->value() >= (navigatorWidget->y() - topSearchArea->y() - this->contentsMargins().top())) {
            qDebug() << "Showing top search area";
            topSearchArea->show();
        } else {
            qDebug() << "Hiding top search area";
            topSearchArea->hide();
        }
    }
}
