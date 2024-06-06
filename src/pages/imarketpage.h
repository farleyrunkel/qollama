#ifndef IMARKETPAGE_H
#define IMARKETPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QScrollArea>
#include <QLabel>
#include <QMap>
#include <QScrollBar>
#include "inavigetrorbar.h"
#include "ilineedit.h"
#include "iscrollarea.h"

/**
 * @class IMarketPage
 * @brief Market page widget
 */
class IMarketPage : public QWidget {
    Q_OBJECT

public:
    explicit IMarketPage(QWidget *parent = nullptr);
    QPushButton* expandButton() const;

private:
    void setupMainLayout();
    void setupTopArea();
    void setupScrollArea();
    void setupConnections();
    void setupTopNavigator();
    void setupTitleLabel();
    void setupSearchLine();
    ILineEdit* createSearchLineEdit();
    void setupNavigator();
    QWidget* createCategoryCard(const QString &categoryName);
    void addCategory(const QString &categoryName);
    void navigateToCategory(const QString &categoryName);
    void setupCategories();
    QPushButton* createButton(const QString& iconPath);

private:
    QVBoxLayout *m_mainLayout;
    QWidget *m_topArea;
    IScrollArea *m_scrollArea;
    QVBoxLayout *m_scrollLayout;
    QWidget *m_scrollWidget;
    QVBoxLayout *m_scrollWidgetLayout;
    QStackedWidget *m_topStack;
    ILineEdit *m_topSearchLine;
    QWidget *m_topSpace;
    INavigetrorBar *m_topNavigator;
    INavigetrorBar *m_navigator;
    QMap<QString, QWidget*> categoryMap;
    QPushButton *m_expandButton;
    QPushButton *m_newChatButton;
    QPushButton *m_userButton;
    ILineEdit *searchLineEdit;
};

#endif // IMARKETPAGE_H
