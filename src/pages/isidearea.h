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

    void load();

    QPushButton *expandButton() const;
    QPushButton *newChatButton() const;
    IOverlayButton *modelsButton() const;
    QPushButton *promptsButton() const;
    QPushButton *settingButton() const;
    IHistoryList *historyList() const;

private:
    void setupMainUi(QWidget* widget);

    void setupTopBar(QWidget *layout);
    void setupTopButtons(QVBoxLayout *layout);
    void setupHistoryList(IHistoryList *layout);
    void setupBottomButtons(QVBoxLayout *layout);

    void setupConnections();

private:
    QPushButton *m_expandButton;
    QPushButton *m_newChatButton;
    IOverlayButton *m_modelsButton;
    QPushButton *m_promptsButton;
    QPushButton *m_settingButton;

    QPushButton* m_messageButton;

    IHistoryList *m_historyList;

    QVBoxLayout* m_mainLayout;
};

#endif // ILEFTWINDOW_H
