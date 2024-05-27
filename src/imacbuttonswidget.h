#ifndef IMACBUTTONSWIDGET_H
#define IMACBUTTONSWIDGET_H

#include <QColor>
#include <QFont>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QApplication>
#include <QPainter>
#include <QRegularExpression>


//{"#DD0000", "#AA8800", "#008800"};



class IMacButton: public QPushButton
{
    Q_OBJECT

public:
    IMacButton(QWidget* parent = nullptr)
        : QPushButton(parent)  {

        setFixedSize(QSize(14, 14));

        defaultStyleSheet = QString(R"(
        QPushButton {
            background-color: red;
            border: 1px solid gray;
            border-radius: 7px;
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


class IMacMaxmizeButton: public QPushButton
{
    Q_OBJECT

public:
    IMacMaxmizeButton(QWidget* parent = nullptr)
        : QPushButton(parent)  {

        setIcon(QIcon(createMacFullScreenIcon(width()-2)));

    }

private:
    QPixmap createMacFullScreenIcon(int size) {
        QPixmap pixmap(size, size);
        pixmap.fill(Qt::transparent);  // 透明背景

        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing);

        // 内部的两个箭头（类似于 macOS 全屏按钮的图标）
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




class IMacButtonsWidget : public QWidget {
    Q_OBJECT

public:
    IMacButtonsWidget(QWidget* parent = nullptr)
        : QWidget(parent){


        closeBtn = new IMacButton(this);
        closeBtn->setBackgroundColor(QColor("#DD0000"));

        minimizeBtn = new IMacButton;
        minimizeBtn->setBackgroundColor(QColor("#AA8800"));

        maximizeBtn = new IMacButton;
        maximizeBtn->setBackgroundColor(QColor("#008800"));

        auto layout = new QHBoxLayout(this);
        layout->addWidget(closeBtn);
        layout->addWidget(minimizeBtn);
        layout->addWidget(maximizeBtn);

        connect(closeBtn, &QPushButton::clicked, qApp, &QApplication::closeAllWindows);
        connect(maximizeBtn, &QPushButton::clicked, this, &IMacButtonsWidget::maximizeWindow);
        connect(minimizeBtn, &QPushButton::clicked, this, &IMacButtonsWidget::minimizeWindow);
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
    IMacButton* closeBtn;
    IMacButton* minimizeBtn;
    IMacButton* maximizeBtn;


};


#endif // IMACBUTTONSWIDGET_H
