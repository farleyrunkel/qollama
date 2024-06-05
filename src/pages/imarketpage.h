#ifndef IMARKETPAGE_H
#define IMARKETPAGE_H

#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QWidget>
#include <QMap>
#include <QDebug>
#include "inavigetrorbar.h"
#include "iscrollarea.h"
#include <QStackedWidget>

class ILineEdit;
class IHPushCard;

class IMarketPage : public QWidget
{
    Q_OBJECT

public:
    explicit IMarketPage(QWidget *parent = nullptr);
    QPushButton* expandButton() const;

private:
    void setupTitleLabel();
    void setupSearchLine();
    void setupNavigator();

    void setupCategories();

    ILineEdit* createSearchLineEdit();
    QWidget* createCategoryCard(const QString &text);
    void addCategory(const QString &text);
    void navigateToCategory(const QString &categoryName);

    QWidget *m_scrollWidget;
    QVBoxLayout *m_scrollWidgetLayout;

    QVBoxLayout *m_scrollLayout;
    QWidget *topSearchArea;
    QHBoxLayout *topAreaButtonsLayout;
    QWidget *navigatorWidget;
    QLabel *titleWidget;
    ILineEdit *searchLineEdit;
    INavigetrorBar* m_navigator;
    INavigetrorBar* m_topNavigator;

    QMap<QString, QWidget*> categoryMap;

    QPushButton* m_expandButton;
    QPushButton* m_userButton;
    QVBoxLayout* m_mainLayout;
    ILineEdit* m_topSearchLine;
    QWidget*     m_topSpace;

    QStackedWidget* m_topStack;
    IScrollArea* m_scrollArea;
    void setupScrollArea();
    void setupTopArea();
    void setupTopNavigator();
protected:



};

#endif // IMARKETPAGE_H
