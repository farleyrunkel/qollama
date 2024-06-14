#ifndef ISETTINGPAGE_H
#define ISETTINGPAGE_H

#include <QFileDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>
#include <QPushButton>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QWidget>

class ISettingPage : public QDialog {
    Q_OBJECT

public:
    // Constructor
    explicit ISettingPage(QWidget *parent = nullptr);

protected:
    void showEvent(QShowEvent *) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void setupMainUi(QWidget *widget);
    void setupCenterWidget(QWidget *widget);

    void setupSideWidget(QWidget *widget);
    void setupRightLayout(QGridLayout *layout);

    void setupSettingsLayout(QStackedLayout *layout);

    void setupOllamaWidget(QWidget *widget);
    void setupPromptWidget(QWidget *widget);
    void setupAccountWidget(QWidget *widget);

    void setupConnections();

    QGroupBox *addSettingGroupBox(const QString &key, const QString &value,
                                  const QString &config = "");

private slots:
    void changeAvatar();

private:
    QHBoxLayout *m_mainLayout;
    QWidget *m_centerWidget;
    QWidget *m_sideArea;
    QStackedLayout *m_settingLayout;

    QPushButton *m_avatarButton;
    QPushButton *m_accountButton;
    QPushButton *m_ollamaButton;
    QPushButton *m_promptButton;
    QPushButton *m_closeButton;

    QWidget *m_accountWidget;
    QWidget *m_ollamaWidget;
    QWidget *m_promptWidget;
};

#endif // ISETTINGPAGE_H
