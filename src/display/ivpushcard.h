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
    explicit IVPushCard(QWidget *parent = nullptr) : QPushButton(parent) {
        setupUI();

        connect(this, &IVPushCard::clicked, [&](){emit ISignalHub::instance().on_IVPushCard_clicked(m_textLabel->text());});
    }

    explicit IVPushCard(const QString &text, QWidget *parent = nullptr) : IVPushCard(parent){
        setText(text);
    }

    IVPushCard(const QIcon& icon, const QString &text, QWidget *parent = nullptr) : IVPushCard(parent){
        setText(text);
        setPixmap(icon.pixmap(m_iconLabel->size()));
    }

    void setupUI() {
        setObjectName("ivPushCard");
        setMinimumSize(QSize(120, 120));
        setMaximumSize(QSize(200, 150));
        setStyleSheet("border: 1px solid gray; border-radius: 15px;");

        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        setSizePolicy(sizePolicy);

        QVBoxLayout *mainLayout = new QVBoxLayout(this);

        setLayout(mainLayout);
        m_iconLabel = new QLabel(this);
        m_iconLabel->setStyleSheet("border: none;");
        m_iconLabel->setMaximumSize(QSize(30, 30));
        m_iconLabel->setAlignment(Qt::AlignCenter); // 设置图标标签居中对齐

        QPixmap pixmap(":/icon/electric-light-bulb.svg");
        m_iconLabel->setPixmap(pixmap.scaled(m_iconLabel->size()));
        mainLayout->addWidget(m_iconLabel, 0, Qt::AlignCenter); // 添加图标标签到布局中并居中对齐

        m_textLabel = new QLabel(this);

        m_textLabel->setSizePolicy(sizePolicy);
        m_textLabel->setAlignment(Qt::AlignCenter); // 设置文本标签居中对齐
        m_textLabel->setWordWrap(true);
        m_textLabel->setIndent(10);
        m_textLabel->setText("dasdfsafdfasdfasd ffasdf asd fasd fasd fasd ffasdf asd fasd fasd fasd fasdf asd fasd fasd fasd fasdf asdf as");
        mainLayout->addWidget(m_textLabel, 0, Qt::AlignCenter); // 添加文本标签到布局中并居中对齐
        m_textLabel->setStyleSheet("border: none;");
    }
    void setText(const QString& text) {
        m_textLabel->setText(text);
    }

    void setPixmap(const QPixmap &pixmap) {
        m_iconLabel->setPixmap(pixmap.scaled(m_iconLabel->size()));
    }

signals:

protected:


private:
    QLabel *m_iconLabel;
    QLabel *m_textLabel;
};

#endif // IVPUSHCARD_H
