#ifndef ILINEEDIT_H
#define ILINEEDIT_H

#include <QApplication>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QWidget>

class ILineEdit : public QLineEdit {
    Q_OBJECT
public:
    ILineEdit(QWidget *parent = nullptr);

    QPushButton *leftButton() const;

    QPushButton *rightButton() const;

private:
    QPushButton *m_leftButton;
    QPushButton *m_rightButton;
    QLineEdit *m_inputLine;
};

#endif // ILINEEDIT_H
