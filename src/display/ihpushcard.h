#ifndef IPUSHCARD_H
#define IPUSHCARD_H

#include <QPushButton>
#include <QLabel>
#include <QIcon>
#include <QHBoxLayout>

class IHPushCard : public QPushButton {
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


    void setIntro(const QString &intro);
    void setName(const QString &name);
protected:
//     // Event filter override
    bool eventFilter(QObject *watched, QEvent *event) override;

protected:
    void resizeEvent(QResizeEvent *event) override
    {
        QPushButton::resizeEvent(event);
        // QFontMetrics fontMetrics(font());
        // QString elidedText = fontMetrics.elidedText(m_intro, Qt::ElideRight, width() - 100); // 调整宽度

        // itemTextLabel->setText(
        //     QString("<b>%1</b><p>%2</p>").arg(m_name).arg(elidedText));
    }

private:
    // void adjustText()
    // {
    //     QFontMetrics fontMetrics(font());
    //     QString elidedText = fontMetrics.elidedText(originalText, Qt::ElideRight, width() - 70); // 调整宽度
    //     setText(elidedText);
    // }

    // QString originalText;

    // void setTextWithElide(const QString &text)
    // {
    //     originalText = text;
    //     adjustText();
    // }

private:
    void setupMainUI();
    void setupTextUI(QHBoxLayout *layout);
    void setupIconUI(QHBoxLayout *layout);
    void setupNumberUI(QHBoxLayout *layout);

private:
    // Member variables
    QLabel *itemNumberLabel; // Label for card number
    QLabel *itemIconLabel; // Label for card icon
    QLabel *itemTextLabel; // Label for card text
    QString m_name;
    QString m_intro;
    QString m_icon;

};

#endif // IPUSHCARD_H
