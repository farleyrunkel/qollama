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
    IOverlayButton *newChatButton() const;
    QPushButton *exploreButton() const;
    QPushButton *settingButton() const;
    IHistoryList *historyList() const;

private:
    void setupConnections();
    void setupTitleBar(QVBoxLayout *layout);
    void setupButtons(QVBoxLayout *layout);
    void setupHistoryList(QVBoxLayout *layout);
    void setupSettingButton(QVBoxLayout *layout);

    QWidget *createButtonContainer(QWidget *parent, const QString &objectName,
                                   const QString &iconPath, const QSize &size,
                                   QVBoxLayout *layout);
    QPushButton *createButton(QWidget *parent, const QString &objectName,
                              const QString &iconPath, const QSize &size,
                              bool isFixedSize = true);
    IOverlayButton *createOverlayButton(QWidget *parent,
                                        const QString &objectName,
                                        const QFont &font, const QSize &size);

private:
    QPushButton *m_expandButton;
    QPushButton *m_newChatButton;
    IOverlayButton *m_modelButton;
    QPushButton *m_exploreButton;
    QPushButton *m_settingButton;
    IHistoryList *m_historyList;
};

#endif // ILEFTWINDOW_H
