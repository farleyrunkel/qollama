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

class ILineEdit;
class IHPushCard;

class IMarketPage : public QScrollArea
{
    Q_OBJECT

public:
    explicit IMarketPage(QWidget *parent = nullptr);

private:
    void setupTitle();
    void setupSearchLine();
    void setupNavigator();
    void setupTopSearchArea();
    void setupCategories();

    ILineEdit* createSearchLineEdit();
    QWidget* createCategoryCard(const QString &text);
    void addCategory(const QString &text);
    void navigateToCategory(const QString &categoryName);

    QWidget *containerWidget;
    QVBoxLayout *contentLayout;
    QVBoxLayout *mainLayout;
    QWidget *topSearchArea;
    QHBoxLayout *topAreaButtonsLayout;
    QWidget *navigatorWidget;
    QLabel *titleWidget;
    ILineEdit *searchLineEdit;
    INavigetrorBar* m_navigator;
    INavigetrorBar* m_topNavigator;

    QMap<QString, QWidget*> categoryMap;

    int initialWidthDifference;
protected:
    void scrollContentsBy(int dx, int dy) override;
    void resizeEvent(QResizeEvent *event) override;
};

#endif // IMARKETPAGE_H
