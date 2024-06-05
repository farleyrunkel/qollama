#ifndef ILEFTWINDOW_H
#define ILEFTWINDOW_H

#include "iwidget.h"
#include <QWidget>
#include <QPushButton>
#include "ioverlaybutton.h"
#include "ihistorylist.h"

class ILeftWindow : public IWidget
{
    Q_OBJECT

public:
    explicit ILeftWindow(QWidget *parent = nullptr);

    QPushButton* expandButton() const;
    IOverlayButton* newChatButton() const;
    QPushButton* exploreButton() const;
    QPushButton *settingButton() const;
    IHistoryList* historyList() const;

private:
    void setupConnections();
    void setupTitleBar(QVBoxLayout *layout);
    void setupButtons(QVBoxLayout *layout);
    void setupHistoryList(QVBoxLayout *layout);
    void setupSettingButton(QVBoxLayout *layout);

    QWidget* createButtonContainer(QWidget *parent, const QString &objectName, const QString &iconPath, const QSize &size, QVBoxLayout *layout);
    QPushButton* createButton(QWidget *parent, const QString &objectName, const QString &iconPath, const QSize &size, bool isFixedSize = true);
    IOverlayButton* createOverlayButton(QWidget *parent, const QString &objectName, const QFont &font, const QSize &size);

    QPushButton *m_expandButton;
    IOverlayButton *m_modelButton;
    QPushButton *m_exploreButton;
    QPushButton *m_settingButton;
    IHistoryList *m_historyList;


};

#endif // ILEFTWINDOW_H
