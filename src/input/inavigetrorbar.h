#ifndef INAVIGETRORBAR_H
#define INAVIGETRORBAR_H

#include "iwidget.h"
#include <QGridLayout>
#include <QLabel>
#include <QMap>
#include <QPushButton>
#include <QWidget>

class INavigetrorBar : public IWidget {
    Q_OBJECT

public:
    explicit INavigetrorBar(QWidget *parent = nullptr);
    void addButton(const QString &text);
    QLabel *getUnderlineLabel(const QString &text) const;
    void showUnderline(QLabel *underlineLabel);

signals:
    void buttonClicked(QPushButton *button);

private:
    QGridLayout *m_buttonLayout;
    QLabel *m_currentUnderlineLabel;
    QMap<QString, QLabel *> m_underlineLabelMap;
};

#endif // INAVIGETRORBAR_H
