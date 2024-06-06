#ifndef IWELCOMEPAGE_H
#define IWELCOMEPAGE_H

#include "ilineedit.h"
#include "ivpushcard.h"
#include "iwidget.h"
#include <QGridLayout>
#include <QLabel>
#include <QMenu>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

/**
 * @class IWelcomePage
 * @brief The IWelcomePage class represents the welcome page of the application.
 */
class IWelcomePage : public IWidget
{
    Q_OBJECT

public:
    explicit IWelcomePage(QWidget *parent = nullptr);

private:
    void setupMainLayout();
    void setupTopArea();
    void setupContentArea();
    void setupContentLabel();
    void setupContentCards();
    void setupContentLineEdit();
    void setupConnections();
    void retranslateUi();
    void updateMenu(const QList<QString> &list);

    QPushButton *createButton(const QString &iconPath);
    IVPushCard *createPushCard(const QString &text, const QString &iconPath);

private:
    QVBoxLayout *m_mainLayout;    ///< Main layout for the welcome page.
    QGridLayout *m_contentLayout; ///< Layout for the content area.
    QWidget *m_topArea;           ///< Widget for the top area.
    QPushButton *m_expandButton;  ///< Button to expand the sidebar.
    QPushButton *m_newChatButton; ///< Button to create a new chat.
    QPushButton *m_userButton;    ///< Button for user settings.
    QLabel *m_welcomeLogo;        ///< Label for the welcome logo.
    ILineEdit *m_inputLine;       ///< Line edit for input messages.
    QMenu *m_menu;                ///< Menu for additional options.

    IVPushCard *m_card1; ///< First push card.
    IVPushCard *m_card2; ///< Second push card.
    IVPushCard *m_card3; ///< Third push card.
    IVPushCard *m_card4; ///< Fourth push card.
};

#endif // IWELCOMEPAGE_H
