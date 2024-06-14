#ifndef IMARKETPAGE_H
#define IMARKETPAGE_H

#include "ihpushcard.h"
#include "ilineedit.h"
#include "inavigetrorbar.h"
#include "iscrollarea.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QMap>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QStackedLayout>

/**
 * @class IMarketPage
 * @brief Market page widget
 */
class IMarketPage : public IWidget {
    Q_OBJECT

public:
    explicit IMarketPage(QWidget *parent = nullptr);

    void load();

private:
    void setupMainUi(QWidget *widget);
    void setupTopBar(QWidget* layout);
    void setupScrollArea(QWidget* layout);
    void setupTopNavigator(QLayout* layout);
    void setupTitleLabel(QLayout* layout);
    void setupSearchLine(QLayout* layout);
    void setupNavigator(QLayout* layout);

    void setupConnections();

    ILineEdit *createSearchLineEdit();
    QWidget *createCategoryCard(const QString &categoryName);

    void addCategory(const QString &categoryName);
    void addCategoryItem(const QString &categoryName, IHPushCard *item);

    void navigateToCategory(const QString &categoryName);

private:
    QVBoxLayout *m_mainLayout;
    QWidget *m_topArea;
    IScrollArea *m_scrollArea;
    QVBoxLayout *m_scrollLayout;
    QWidget *m_scrollWidget;
    QVBoxLayout *m_scrollWidgetLayout;
    QStackedLayout *m_topStack;
    ILineEdit *m_topSearchLine;
    QWidget *m_topSpace;
    INavigetrorBar *m_topNavigator;
    INavigetrorBar *m_navigator;
    QMap<QString, QWidget *> categoryMap;
    QPushButton *m_expandButton;
    QPushButton *m_newChatButton;
    QPushButton *m_userButton;
    ILineEdit *searchLineEdit;

    QMap<QString, QWidget *> m_categories;
};

#endif // IMARKETPAGE_H
