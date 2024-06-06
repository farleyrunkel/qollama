#ifndef IVPUSHCARD_H
#define IVPUSHCARD_H

#include <QIcon>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QVBoxLayout>

class IVPushCard : public QPushButton {
    Q_OBJECT

public:
    // Constructors
    explicit IVPushCard(QWidget *parent = nullptr);
    IVPushCard(const QString &text, QWidget *parent = nullptr);
    IVPushCard(const QIcon &icon, const QString &text, QWidget *parent = nullptr);

    // Setters
    void setText(const QString &text);     // Set card text
    void setPixmap(const QPixmap &pixmap); // Set card icon

private:
    // Private method for UI setup
    void setupUI();

    // Member variables
    QLabel *m_iconLabel; // Label for card icon
    QLabel *m_textLabel; // Label for card text
};

#endif // IVPUSHCARD_H
