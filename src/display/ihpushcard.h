#ifndef IPUSHCARD_H
#define IPUSHCARD_H

#include <QFrame>
#include <QLabel>
#include <QIcon>

class IHPushCard : public QFrame {
    Q_OBJECT

public:
    // Constructors
    IHPushCard(QWidget *parent = nullptr);
    IHPushCard(int num, QWidget *parent = nullptr) : IHPushCard(parent) {
        setNumber(num);
    };

    // Setters
    void setNumber(int num); // Set card number
    void setText(const QString &text); // Set card text
    void setNumberUnused(); // Set card as unused
    void setIcon(const QIcon &icon); // Set card icon

protected:
    // Event filter override
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    // Private method for UI setup
    void setupUI();

private:
    // Member variables
    QLabel *itemNumberLabel; // Label for card number
    QLabel *itemIconLabel; // Label for card icon
    QLabel *itemTextLabel; // Label for card text
};

#endif // IPUSHCARD_H
