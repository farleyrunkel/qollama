#ifndef IGPTSWIDGET_H
#define IGPTSWIDGET_H

#include <QWidget>
#include <QHBoxLayout>

class IGptsWidget : public QWidget
{
    Q_OBJECT
public:
    IGptsWidget();

    void setupMainUi() {

        setObjectName("ISettingPage");
        setContentsMargins(80, 80, 80, 80);
        setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
        setAttribute(Qt::WA_TranslucentBackground);

        m_mainLayout = new QHBoxLayout(this);
        setLayout(m_mainLayout);
    };


    QHBoxLayout* m_mainLayout;
};

#endif // IGPTSWIDGET_H
