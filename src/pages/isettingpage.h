#ifndef ISETTINGPAGE_H
#define ISETTINGPAGE_H

#include <QFileDialog>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>
#include <QPushButton>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QGroupBox>

class ISettingPage : public QDialog {
    Q_OBJECT

public:
    // Constructor
    explicit ISettingPage(QWidget *parent = nullptr);

protected:
    void showEvent(QShowEvent *) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void setupMainUi(QWidget* widget = nullptr);
    void setupCenterWidget(QWidget *);

    void setupSideWidget(QWidget* widget = nullptr);
    void setupSettingsArea(QGridLayout *);

    void setupSettingsLayout(QStackedLayout *widget);

    void setupOllamaSettings(QWidget* );
    void setupPromptSettings(QWidget* );
    void setupAccountSettings(QWidget* );

    void setupConnections();

    QGroupBox *addSettingGroupBox(const QString &key, const QString &value, const QString &config = "");

private slots:
    void changeAvatar();

private:
    QHBoxLayout *m_mainLayout;
    QWidget* m_centerWidget;
    QWidget *m_sideArea;
    QStackedLayout *m_settingLayout;

    QPushButton *m_avatarButton;
    QPushButton *m_accountButton;
    QPushButton *m_ollamaButton;
    QPushButton *m_promptButton;
    QPushButton *m_closeButton;

    QWidget* m_accountWidget;
    QWidget* m_ollamaWidget;
    QWidget* m_promptWidget;
};

#endif // ISETTINGPAGE_H
