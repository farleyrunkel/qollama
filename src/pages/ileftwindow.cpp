#include "ileftwindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include "ihistorylist.h"
#include "ioverlaybutton.h"

ILeftWindow::ILeftWindow(QWidget *parent) : IWidget(parent) {

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

    m_expandButton = new QPushButton(leftTitleBar);
    m_expandButton->setObjectName("expandSideBtn");
    QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    m_expandButton->setSizePolicy(sizePolicy);
    m_expandButton->setMinimumSize(QSize(30, 30));
    m_expandButton->setMaximumSize(QSize(30, 30));
    QIcon icon1;
    icon1.addFile(QString::fromUtf8(":/icon/sidebar-left.svg"), QSize(), QIcon::Normal, QIcon::Off);
    m_expandButton->setIcon(icon1);
    horizontalLayout_5->addWidget(m_expandButton);

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

    m_newChatButton = new INewChatButton(sideWidget);
    m_newChatButton->setObjectName("newChatButton");
    m_newChatButton->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
    m_newChatButton->setMinimumSize(QSize(0, 34));
    m_newChatButton->setMaximumSize(QSize(16777215, 34));
    QFont font2;
    font2.setFamilies({QString::fromUtf8("Microsoft YaHei UI")});
    font2.setPointSize(10);
    font2.setWeight(QFont::Medium);
    m_newChatButton->setFont(font2);
    m_newChatButton->setFocusPolicy(Qt::NoFocus);
    m_newChatButton->setLayoutDirection(Qt::LeftToRight);
    //newChatButton->setIcon(icon);
    verticalLayout->addWidget(m_newChatButton);

    m_exploreButton = new QPushButton(sideWidget);
    m_exploreButton->setObjectName("exploreButton");
    m_exploreButton->setMinimumSize(QSize(0, 34));
    m_exploreButton->setMaximumSize(QSize(16777215, 34));
    m_exploreButton->setFont(font2);
    QIcon icon3;
    icon3.addFile(QString::fromUtf8(":/icon/sparkles.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_exploreButton->setIcon(icon3);
    verticalLayout->addWidget(m_exploreButton);

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

    m_expandButton->setToolTip(QCoreApplication::translate("MainWindow", "Expand", nullptr));
    newChatBtn->setToolTip(QCoreApplication::translate("MainWindow", "Llama3", nullptr));
    m_newChatButton->setText(QCoreApplication::translate("MainWindow", "Llama3", nullptr));
    m_exploreButton->setText(QCoreApplication::translate("MainWindow", "Explore", nullptr));
    settingButton->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
}
