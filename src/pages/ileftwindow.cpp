#include "ileftwindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include "ihistorylist.h"
#include "ioverlaybutton.h"

ILeftWindow::ILeftWindow(QWidget *parent) : QWidget(parent) {

    setupUi();
}

void ILeftWindow::setupUi() {

    setMaximumSize(QSize(200, 16777215));

    QVBoxLayout *verticalLayout_3 = new QVBoxLayout(this);
    verticalLayout_3->setSpacing(0);
    verticalLayout_3->setObjectName("verticalLayout_3");
    verticalLayout_3->setContentsMargins(0, 0, 0, 0);

    QWidget *sideWidget = new QWidget(this);
    sideWidget->setObjectName("sideWidget");
    QVBoxLayout *verticalLayout = new QVBoxLayout(sideWidget);
    verticalLayout->setObjectName("verticalLayout");
    verticalLayout->setContentsMargins(-1, 0, -1, -1);

    QWidget *leftTitleBar = new QWidget(sideWidget);
    leftTitleBar->setObjectName("leftTitleBar");
    QHBoxLayout *horizontalLayout_5 = new QHBoxLayout(leftTitleBar);
    horizontalLayout_5->setSpacing(0);
    horizontalLayout_5->setObjectName("horizontalLayout_5");
    horizontalLayout_5->setContentsMargins(0, 0, 0, 0);

    auto expandSideBtn = new QPushButton(leftTitleBar);
    expandSideBtn->setObjectName("expandSideBtn");
    QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    expandSideBtn->setSizePolicy(sizePolicy);
    expandSideBtn->setMinimumSize(QSize(30, 30));
    expandSideBtn->setMaximumSize(QSize(30, 30));
    QIcon icon1;
    icon1.addFile(QString::fromUtf8(":/icon/sidebar-left.svg"), QSize(), QIcon::Normal, QIcon::Off);
    expandSideBtn->setIcon(icon1);
    horizontalLayout_5->addWidget(expandSideBtn);

    QSpacerItem *horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
    horizontalLayout_5->addItem(horizontalSpacer_5);

    auto newChatBtn = new QPushButton(leftTitleBar);
    newChatBtn->setObjectName("newChatBtn");
    newChatBtn->setSizePolicy(sizePolicy);
    newChatBtn->setMinimumSize(QSize(30, 30));
    newChatBtn->setMaximumSize(QSize(30, 30));
    QIcon icon2;
    icon2.addFile(QString::fromUtf8(":/icon/create-new.svg"), QSize(), QIcon::Normal, QIcon::Off);
    newChatBtn->setIcon(icon2);
    horizontalLayout_5->addWidget(newChatBtn);

    verticalLayout->addWidget(leftTitleBar);

    auto newChatButton = new INewChatButton(sideWidget);
    newChatButton->setObjectName("newChatButton");
    newChatButton->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
    newChatButton->setMinimumSize(QSize(0, 34));
    newChatButton->setMaximumSize(QSize(16777215, 34));
    QFont font2;
    font2.setFamilies({QString::fromUtf8("Microsoft YaHei UI")});
    font2.setPointSize(10);
    font2.setWeight(QFont::Medium);
    newChatButton->setFont(font2);
    newChatButton->setFocusPolicy(Qt::NoFocus);
    newChatButton->setLayoutDirection(Qt::LeftToRight);
    //newChatButton->setIcon(icon);
    verticalLayout->addWidget(newChatButton);

    auto exploreButton = new QPushButton(sideWidget);
    exploreButton->setObjectName("exploreButton");
    exploreButton->setMinimumSize(QSize(0, 34));
    exploreButton->setMaximumSize(QSize(16777215, 34));
    exploreButton->setFont(font2);
    QIcon icon3;
    icon3.addFile(QString::fromUtf8(":/icon/sparkles.png"), QSize(), QIcon::Normal, QIcon::Off);
    exploreButton->setIcon(icon3);
    verticalLayout->addWidget(exploreButton);

    auto historyList = new IHistoryList(sideWidget);
    historyList->setObjectName("historyList");
    historyList->setFocusPolicy(Qt::NoFocus);
    historyList->setFrameShape(QFrame::NoFrame);
    historyList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    historyList->setProperty("showDropIndicator", QVariant(false));
    historyList->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    verticalLayout->addWidget(historyList);

    auto settingButton = new QPushButton(sideWidget);
    settingButton->setObjectName("settingButton");
    settingButton->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
    settingButton->setMinimumSize(QSize(0, 40));
    settingButton->setMaximumSize(QSize(16777215, 40));
    settingButton->setFont(font2);
    QIcon icon4;
    icon4.addFile(QString::fromUtf8(":/icon/gear.svg"), QSize(), QIcon::Normal, QIcon::Off);
    settingButton->setIcon(icon4);
    settingButton->setIconSize(QSize(20, 20));
    verticalLayout->addWidget(settingButton);

    verticalLayout_3->addWidget(sideWidget);

    expandSideBtn->setToolTip(QCoreApplication::translate("MainWindow", "Expand", nullptr));
    newChatBtn->setToolTip(QCoreApplication::translate("MainWindow", "Llama3", nullptr));
    newChatButton->setText(QCoreApplication::translate("MainWindow", "Llama3", nullptr));
    exploreButton->setText(QCoreApplication::translate("MainWindow", "Explore", nullptr));
    settingButton->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
}
