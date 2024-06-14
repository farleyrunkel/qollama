#ifndef IMODELSPAGE_H
#define IMODELSPAGE_H

#include "gallerywidget.h"

class IModelsPage : public QWidget
{
    Q_OBJECT
public:
    IModelsPage(QWidget* parent = nullptr);

    void load();

private:
    void setupMainUi(QWidget *);
    void setupConnections();
    void setupTopArea(QWidget *widget);
    void setupChatArea(QWidget* widget);


    QWidget *m_topArea;
    GalleryWidget *m_chatsStack;
    QVBoxLayout *m_mainLayout;
    QPushButton *m_expandButton;
    QPushButton *m_newChatButton;
    QPushButton *m_userButton;
};

#endif // IMODELSPAGE_H
