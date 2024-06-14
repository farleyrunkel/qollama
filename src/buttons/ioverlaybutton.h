#ifndef IOVERLAYBUTTON_H
#define IOVERLAYBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QList>

class ISubButton : public QPushButton {
    Q_OBJECT
public:
    ISubButton(QWidget *parent = nullptr) : QPushButton(parent) {
        setStyleSheet("border: none;"); // Remove border
    }

protected:
    void enterEvent(QEnterEvent *event) override {
        QPushButton::enterEvent(event);
        setEnabled(true); // Enable the button on hover enter
    }

    void leaveEvent(QEvent *event) override {
        QPushButton::leaveEvent(event);
        setEnabled(false); // Disable the button on hover leave
    }
};

class IOverlayButton : public QPushButton {
    Q_OBJECT

public:
    explicit IOverlayButton(QWidget *parent = nullptr);

    void addSubButton(QIcon icon);
    QList<QPushButton *> subButtons() const;
    QPushButton *getSubButton(int index) const;
    QPushButton *subButton(int i) const;

protected:
    bool event(QEvent *e) override;

private slots:
    void showSubButtons();
    void hideSubButtons();

private:
    QHBoxLayout *m_mainLayout;
    QList<QPushButton *> m_subButtons;
};

#endif // IOVERLAYBUTTON_H
