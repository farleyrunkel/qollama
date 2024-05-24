#ifndef IGALLERYWIDGET_H
#define IGALLERYWIDGET_H

#include <QScrollArea>
#include <QHBoxLayout>
#include <QLCDNumber>
#include <QPushButton>
#include <QSpacerItem>
#include <QDebug>
#include <QScrollBar>
#include <QLabel>


class IGalleryItem : public QFrame
{
    Q_OBJECT

public:
    IGalleryItem(QWidget* parent = nullptr) : QFrame(parent) {

        setupUI();
    }

private:
    void setupUI() {

        setMinimumWidth(150);
        setMinimumHeight(40);
        setMaximumWidth(450);
        setMaximumHeight(50);
        setStyleSheet("border: 1px solid red");
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        numbLabel = new QLabel(this);
        numbLabel->setNum(1);
        numbLabel->setFixedWidth(30);

        iconLabel = new QLabel(this);
        iconLabel->setPixmap(QIcon::fromTheme(QIcon::ThemeIcon::AudioCard).pixmap(30));
        iconLabel->setFixedWidth(40);
        textLabel = new QLabel(this);
        textLabel->setText("<b>Heading</b>"
                   "<p>This is a paragraph.</p>");

        auto mainLayout = new QHBoxLayout;

        mainLayout->addWidget(numbLabel);
        mainLayout->addWidget(iconLabel);
        mainLayout->addWidget(textLabel);
        mainLayout->setSpacing(2);
        mainLayout->setContentsMargins(1, 2, 1, 2);

        setLayout(mainLayout);
    }
private:
    QLabel* numbLabel;
    QLabel* iconLabel;
    QLabel* textLabel;
};



class IGalleryColumn : public QWidget
{
    Q_OBJECT

public:
    IGalleryColumn(QWidget* parent = nullptr)
        : QWidget(parent)
        , lastLayoutIndex(0)
        , mainLayout(new QVBoxLayout(this))
        , numLayouts(3)
    {
        setStyleSheet("border: 1px solid red");
        setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        setLayout(mainLayout);
        qDebug() << "IGalleryColumn created";

        for (int i = 0; i < numLayouts; ++i) {
            auto spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding  );
            spacers.push_back(spacer);
            mainLayout->addSpacerItem(spacer);
            qDebug() << "Added QVBoxLayout with QSpacerItem to IGalleryColumn";
        }
    }

    void addItem(IGalleryItem* item) {
        if (lastLayoutIndex >= spacers.size()) {
            qDebug() << "No more layouts available to add items";
            return;
        }
        mainLayout->removeItem(spacers[lastLayoutIndex]);
        mainLayout->insertWidget(lastLayoutIndex, item);

        qDebug() << "Added item to layout" << lastLayoutIndex;
        lastLayoutIndex++;
    }

    bool allItemsAdded() const {
        return lastLayoutIndex >= spacers.size();
    }

private:
    int lastLayoutIndex;
    const int numLayouts;
    QVBoxLayout* mainLayout;

    std::vector<QSpacerItem*> spacers;
};

class IGalleryList : public QWidget
{
    Q_OBJECT

public:
    IGalleryList(QWidget* parent = nullptr)
        : QWidget(parent)
    {
        mainLayout = new QGridLayout;
        setLayout(mainLayout);
        mainLayout->setAlignment(Qt::AlignLeft);

        mainLayout->addWidget(new IGalleryItem, 0, 0);
         mainLayout->addWidget(new IGalleryItem, 0, 1);
       mainLayout->addWidget(new IGalleryItem);
         mainLayout->addWidget(new IGalleryItem);
         mainLayout->addWidget(new IGalleryItem);
         mainLayout->addWidget(new IGalleryItem);
                 mainLayout->addWidget(new IGalleryItem);
    }

private:
    QGridLayout* mainLayout;
};


class IGalleryWidget : public QScrollArea
{
    Q_OBJECT
public:
    IGalleryWidget(QWidget* parent = nullptr)
        : QScrollArea(parent)
        , container(new QWidget(this))
        , lastColumn(nullptr)
    {
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        setFixedHeight(320);
        setWidgetResizable(true);
        setWidget(container);

        mainLayout = new QHBoxLayout(container);
        container->setLayout(mainLayout);
        mainLayout->addStretch(1);

        auto buttonLayout = new QHBoxLayout;
        leftButton = new QPushButton("<", this);
        rightButton = new QPushButton(">", this);
        buttonLayout->addWidget(leftButton);
        buttonLayout->addStretch(1);
        buttonLayout->addWidget(rightButton);

        auto mainContainerLayout = new QVBoxLayout(this);
        mainContainerLayout->addLayout(buttonLayout);

        setLayout(mainContainerLayout);

        connect(leftButton, &QPushButton::clicked, this, &IGalleryWidget::scrollLeft);
        connect(rightButton, &QPushButton::clicked, this, &IGalleryWidget::scrollRight);

        for (int i = 0; i < 15; i++) {
            addItem();
        }
    }

    void addItem() {

        addItem(new IGalleryItem);
    }
    void addItem(IGalleryItem* item) {
        if (!lastColumn || lastColumn->allItemsAdded()) {
            lastColumn = new IGalleryColumn;
            mainLayout->insertWidget(mainLayout->count() - 1, lastColumn);
        }
        lastColumn->addItem(item);
    }

    void scrollLeft() {
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - 10);
    }

    void scrollRight() {
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() + 10);
    }

private:
    QWidget* container;
    QHBoxLayout* mainLayout;
    IGalleryColumn* lastColumn;
    QPushButton* leftButton;
    QPushButton* rightButton;
};

#endif // IGALLERYWIDGET_H
