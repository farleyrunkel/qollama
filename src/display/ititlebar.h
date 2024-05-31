#ifndef ITITLEBAR_H
#define ITITLEBAR_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QFont>
#include <QIcon>

class ITitleBar : public QWidget
{
    Q_OBJECT

public:
    ITitleBar(QWidget *parent = nullptr) : QWidget(parent) {
        setupUI();
    }

    void setExpandButtonIcon(const QIcon &icon) {
        if (expandButton) {
            expandButton->setIcon(icon);
        }
    }

    void setComboBoxItems(const QStringList &items) {
        if (comboBox) {
            comboBox->clear();
            comboBox->addItems(items);
        }
    }

    void setUserButtonIcon(const QIcon &icon) {
        if (userButton) {
            userButton->setIcon(icon);
        }
    }

    void setUserButtonTooltip(const QString &tooltip) {
        if (userButton) {
            userButton->setToolTip(tooltip);
        }
    }

private:
    QWidget *titleBar;
    QPushButton *expandButton;
    QComboBox *comboBox;
    QPushButton *userButton;

    void setupUI() {
        titleBar = createTitleBar();
        QHBoxLayout *rightTitleBar = createTitleBarLayout();
        rightTitleBar->addWidget(createExpandButton());
        rightTitleBar->addWidget(createComboBox());
        rightTitleBar->addItem(createHorizontalSpacer());
        rightTitleBar->addWidget(createUserButton());
    }

    QWidget* createTitleBar() {
        QWidget *titleBar = new QWidget(this);
        titleBar->setObjectName("titleBar");

        QSizePolicy titleBarSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        titleBarSizePolicy.setHeightForWidth(titleBar->sizePolicy().hasHeightForWidth());
        titleBar->setSizePolicy(titleBarSizePolicy);
        titleBar->setMinimumSize(QSize(0, 30));
        titleBar->setMaximumSize(QSize(16777215, 30));

        return titleBar;
    }

    QHBoxLayout* createTitleBarLayout() {
        QHBoxLayout *rightTitleBar = new QHBoxLayout(titleBar);
        rightTitleBar->setSpacing(11);
        rightTitleBar->setContentsMargins(11, 0, 11, 0);
        return rightTitleBar;
    }

    QPushButton* createExpandButton() {
        expandButton = new QPushButton(titleBar);
        expandButton->setObjectName("expandButton");

        QSizePolicy buttonSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        buttonSizePolicy.setHeightForWidth(expandButton->sizePolicy().hasHeightForWidth());
        expandButton->setSizePolicy(buttonSizePolicy);
        expandButton->setMinimumSize(QSize(30, 30));
        expandButton->setMaximumSize(QSize(30, 30));

        expandButton->setFlat(true);

        return expandButton;
    }

    QComboBox* createComboBox() {
        comboBox = new QComboBox(titleBar);
        comboBox->setObjectName("comboBox");

        QSizePolicy comboBoxSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        comboBoxSizePolicy.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(comboBoxSizePolicy);
        comboBox->setMaximumSize(QSize(88, 16777215));

        QFont comboBoxFont;
        comboBoxFont.setFamilies({QString::fromUtf8("Microsoft YaHei UI")});
        comboBoxFont.setPointSize(10);
        comboBoxFont.setBold(true);
        comboBox->setFont(comboBoxFont);
        comboBox->setStyleSheet("color: rgb(112, 112, 112);");
        comboBox->setMinimumContentsLength(0);
        comboBox->setFrame(true);

        return comboBox;
    }

    QSpacerItem* createHorizontalSpacer() {
        return new QSpacerItem(552, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    }

    QPushButton* createUserButton() {
        userButton = new QPushButton(titleBar);
        userButton->setObjectName("userButton");

        QSizePolicy buttonSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        buttonSizePolicy.setHeightForWidth(userButton->sizePolicy().hasHeightForWidth());
        userButton->setSizePolicy(buttonSizePolicy);
        userButton->setMaximumSize(QSize(20, 20));

        userButton->setLayoutDirection(Qt::LeftToRight);
        userButton->setCheckable(false);
        userButton->setAutoDefault(false);
        userButton->setFlat(false);

        return userButton;
    }
};

#endif // ITITLEBAR_H
