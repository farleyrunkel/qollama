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


//{"#DD0000", "#AA8800", "#008800"};



class IWinButton: public QPushButton
{
    Q_OBJECT

public:
    IWinButton(QWidget* parent = nullptr)
        : QPushButton(parent)  {

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
        newStyleSheet.replace(QRegularExpression("background-color\\s*:\\s*\\w+;"), "background-color: " + colorStr + ";");
        setStyleSheet(newStyleSheet);
        update();
    }

private:
    QString defaultStyleSheet;
};


class IWinMaxmizeButton: public QPushButton
{
    Q_OBJECT

public:
    IWinMaxmizeButton(QWidget* parent = nullptr)
        : QPushButton(parent)  {

        setIcon(QIcon(createWinFullScreenIcon(width()-2)));

    }

private:
    QPixmap createWinFullScreenIcon(int size) {
        QPixmap pixmap(size, size);
        pixmap.fill(Qt::transparent);  // 透明背景

        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing);

        // 内部的两个箭头（类似于 WinOS 全屏按钮的图标）
        QPen arrowPen(Qt::white, size / 10);
        painter.setPen(arrowPen);

        int offset = size / 4;
        QPointF points[3] = {
            QPointF(offset, offset),
            QPointF(size / 2, size / 2),
            QPointF(offset, size - offset)
        };
        painter.drawPolyline(points, 3);

        points[0] = QPointF(size - offset, size - offset);
        points[1] = QPointF(size / 2, size / 2);
        points[2] = QPointF(size - offset, offset);
        painter.drawPolyline(points, 3);

        return pixmap;
    }
};




class IWinButtonsWidget : public QWidget {
    Q_OBJECT

public:
    IWinButtonsWidget(QWidget* parent = nullptr)
        : QWidget(parent){

        setFixedWidth(100);
        closeBtn = new IWinButton(this);
        closeBtn->setBackgroundColor(QColor("#DD0000"));
        closeBtn->setIcon(QIcon("://icon/window-close-line.svg"));

        minimizeBtn = new IWinButton;
        minimizeBtn->setBackgroundColor(QColor("#AA8800"));
        minimizeBtn->setIcon(QIcon("://icon/window-minimize.svg"));

        maximizeBtn = new IWinButton;
        maximizeBtn->setBackgroundColor(QColor("#008800"));
        maximizeBtn->setIcon(QIcon("://icon/window-max-line.svg"));

        auto layout = new QHBoxLayout(this);

        layout->addWidget(minimizeBtn);
        layout->addWidget(maximizeBtn);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);
        layout->addWidget(closeBtn);
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

    QString styleSheet;
    IWinButton* closeBtn;
    IWinButton* minimizeBtn;
    IWinButton* maximizeBtn;
};

#endif // IWINBUTTONSWIDGET_H
