#ifndef IWINBUTTONSWIDGET_H
#define IWINBUTTONSWIDGET_H

#include <QColor>
#include <QFont>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QApplication>
#include <QPainter>
#include <QRegularExpression>

class IWinButton : public QPushButton
{
    Q_OBJECT

public:
    IWinButton(QWidget* parent = nullptr)
        : QPushButton(parent)
    {
        setFixedHeight(30);
        setFixedWidth(40);

        defaultStyleSheet = QString(R"(
        QPushButton {
            border: 1px hidden gray;
            text-align: center;
        }
        )");

        setStyleSheet(defaultStyleSheet);
    }

    void setBackgroundColor(QColor color) {
        QString colorStr = color.name();  // Get the color name as a string
        QString newStyleSheet = defaultStyleSheet;
        if (newStyleSheet.contains(QRegularExpression("background-color\\s*:\\s*#[0-9a-fA-F]+;"))) {
            newStyleSheet.replace(QRegularExpression("background-color\\s*:\\s*#[0-9a-fA-F]+;"), "background-color: " + colorStr + ";");
        } else {
            newStyleSheet += QString("background-color: %1;").arg(colorStr);
        }
        setStyleSheet(newStyleSheet);
        update();
    }

private:
    QString defaultStyleSheet;
};

class IWinButtonsWidget : public QWidget
{
    Q_OBJECT

public:
    IWinButtonsWidget(QWidget* parent = nullptr)
        : QWidget(parent)
    {
        setFixedWidth(120);

        minimizeBtn = new IWinButton(this);
        //minimizeBtn->setBackgroundColor(QColor("#AA8800"));
        minimizeBtn->setIcon(QIcon(":/icon/window-minimize.svg"));

        maximizeBtn = new IWinButton(this);
       // maximizeBtn->setBackgroundColor(QColor("#008800"));
        maximizeBtn->setIcon(QIcon(":/icon/window-max-line.svg"));

        closeBtn = new IWinButton(this);
        //closeBtn->setBackgroundColor(QColor("#DD0000"));
        closeBtn->setIcon(QIcon(":/icon/window-close-line.svg"));
        closeBtn->setObjectName("winCloseButton");

        auto layout = new QHBoxLayout(this);

        layout->addWidget(minimizeBtn);
        layout->addWidget(maximizeBtn);
        layout->addWidget(closeBtn);

        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);

        // Hover effect using QSS
        closeBtn->setStyleSheet(closeBtn->styleSheet() + " QPushButton:hover { background-color: #e81123; }");

        connect(closeBtn, &QPushButton::clicked, qApp, &QApplication::closeAllWindows);
        connect(maximizeBtn, &QPushButton::clicked, this, &IWinButtonsWidget::maximizeWindow);
        connect(minimizeBtn, &QPushButton::clicked, this, &IWinButtonsWidget::minimizeWindow);
    }

public slots:
    void maximizeWindow() {
        if (window()->isMaximized()) {
            window()->showNormal();  // Restore window size if already maximized
        } else {
            window()->showMaximized();  // Maximize window if not already maximized
        }
    }

    void minimizeWindow() {
        window()->showMinimized();  // Minimize the window
    }

private:
    IWinButton* closeBtn;
    IWinButton* minimizeBtn;
    IWinButton* maximizeBtn;
};

#endif // IWINBUTTONSWIDGET_H
