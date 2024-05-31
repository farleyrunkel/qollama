#ifndef ICHATSPAGE_H
#define ICHATSPAGE_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include "iwidget.h"
#include <QStackedWidget>
#include "ilineedit.h"
#include "ititlebar.h"

class IChatsPage : public QWidget
{
    Q_OBJECT

    INJECT_SHOW_HIDE_EVENTS(IChatsPage)

public:
    explicit IChatsPage(QWidget *parent = nullptr): QWidget(parent) {

        setupUI();
    };

signals:


private:
    void setupUI() {

        mainLayout = new QVBoxLayout;
        setLayout(mainLayout);

        chatsContainer = new QStackedWidget;

        mainLayout->addWidget(new ITitleBar);

        mainLayout->addWidget(new QWidget);

        mainLayout->addWidget(chatsContainer);

        mainLayout->addWidget(new ILineEdit);
    }


private:
    QVBoxLayout* mainLayout;
    QStackedWidget* chatsContainer;
    QWidget* titleWidget;
    ILineEdit* lineEdit;

};

#endif // ICHATSPAGE_H
