#ifndef IOVERLAYBUTTON_H
#define IOVERLAYBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QList>

class IOverlayButton : public QPushButton {
    Q_OBJECT

public:
    explicit IOverlayButton(QWidget *parent = nullptr);

    void addSubButton(QIcon icon);
    QList<QPushButton *> getSubButtons() const;
    QPushButton *getSubButton(int index) const;

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
