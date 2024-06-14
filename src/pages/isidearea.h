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

    QPushButton *expandButton() const;
    IOverlayButton *modelsButton() const;
    QPushButton *promptsButton() const;
    QPushButton *settingButton() const;
    IHistoryList *historyList() const;

private:
    void setupConnections();
    void setupTitleBar(QLayout *layout);
    void setupTopButtons(QLayout *layout);
    void setupHistoryList(QLayout *layout);
    void setupBottomButtons(QLayout *layout);

private:
    QPushButton *m_expandButton;
    QPushButton *m_newChatButton;
    IOverlayButton *m_modelsButton;
    QPushButton *m_promptsButton;
    QPushButton *m_settingButton;

    QPushButton* m_messageButton;

    IHistoryList *m_historyList;

    QVBoxLayout* m_mainLayout;
    QList<QLayout*>  m_layouts;
    void setupMainUi(QVBoxLayout* layout);

    QLayout *layout(int i) const;
};

#endif // ILEFTWINDOW_H
