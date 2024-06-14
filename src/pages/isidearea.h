#ifndef ILEFTWINDOW_H
#define ILEFTWINDOW_H

#include "ihistorylist.h"
#include "ioverlaybutton.h"
#include "iwidget.h"
#include <QPushButton>
#include <QWidget>

class ISideArea : public IWidget {
    Q_OBJECT

public:
    explicit ISideArea(QWidget *parent = nullptr);
    ~ISideArea();

    QPushButton *expandButton() const;
    QPushButton *newChatButton() const;
    IOverlayButton *modelsButton() const;
    QPushButton *promptsButton() const;
    QPushButton *settingButton() const;
    IHistoryList *historyList() const;

    void load();
private:

    void setupMainLayout(QVBoxLayout* layout);

    void setupTopBar(QWidget *layout);
    void setupTopButtons(QWidget *layout);
    void setupHistoryList(QWidget *layout);
    void setupBottomButtons(QWidget *layout);

    void setupConnections();

    QWidget *widget(int i) const;

private:
    QPushButton *m_expandButton;
    QPushButton *m_newChatButton;
    IOverlayButton *m_modelsButton;
    QPushButton *m_promptsButton;
    QPushButton *m_settingButton;

    QPushButton* m_messageButton;

    IHistoryList *m_historyList;

    QVBoxLayout* m_mainLayout;
    QList<QWidget*>  m_widgets;
};

#endif // ILEFTWINDOW_H
