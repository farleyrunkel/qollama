#ifndef IMESSAGEBOX_H
#define IMESSAGEBOX_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include "spinner/waitingspinnerwidget.h"
#include "iautoresizetextbrowser.h"

class IMessageBox : public QWidget {
    Q_OBJECT

public:
    explicit IMessageBox(const QString& userName, const QString& avatar, const QString& message, QWidget* parent = nullptr);

    QString message() {return m_message;}
    QString role() {return userLabel->text() == "llama3" ? "assistant" : "user";}

protected:
    void resizeEvent(QResizeEvent *event) override;

public slots:
    void setMarkdown(const QString& markdown);
    void appendMessage(const QString& message);
    void finish();
    void setAvatar(const QString &avatar);

private:
    void setAnimation();
    void setupUI();

private:
    QLabel* avatarLabel;
    QLabel* userLabel;
    IAutoResizeTextBrowser* messageBrowser;
    WaitingSpinnerWidget* spinner;

    QString m_message;
};

#endif // IMESSAGEBOX_H
