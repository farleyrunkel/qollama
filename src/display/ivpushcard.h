#ifndef IVPUSHCARD_H
#define IVPUSHCARD_H

#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QEvent>
#include "isignalhub.h"

class IVPushCard : public QPushButton {
    Q_OBJECT
public:
    explicit IVPushCard(QWidget *parent = nullptr);

    explicit IVPushCard(const QString &text, QWidget *parent = nullptr);

    IVPushCard(const QIcon& icon, const QString &text, QWidget *parent = nullptr);

    void setupUI();

    void setText(const QString& text);

    void setPixmap(const QPixmap &pixmap);

signals:

protected:


private:
    QLabel *m_iconLabel;
    QLabel *m_textLabel;
};

#endif // IVPUSHCARD_H
