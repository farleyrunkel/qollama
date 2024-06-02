#ifndef ILEFTWINDOW_H
#define ILEFTWINDOW_H

#include <QWidget>
#include <QPushButton>
#include "ioverlaybutton.h"
#include "iwidget.h"

class ILeftWindow: public IWidget
{
    Q_OBJECT

    //INJECT_SHOW_HIDE_EVENTS(ILeftWindow)

public:
    ILeftWindow(QWidget* parent = nullptr);;

    QPushButton* exploreButton(){return m_exploreButton;};
    IOverlayButton* newChatButton(){return m_newChatButton;};
    QPushButton* expandButton(){return m_expandButton;};

    void setupUi();
private:
    QPushButton* m_exploreButton;
        QPushButton* m_expandButton;
   IOverlayButton* m_newChatButton;
};

#endif // ILEFTWINDOW_H
