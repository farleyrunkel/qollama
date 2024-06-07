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

class ISettingPage : public QDialog {
    Q_OBJECT

public:
    explicit ISettingPage(QWidget *parent = nullptr);

protected:
    void showEvent(QShowEvent *) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void setupMainLayout();
    void setupSideArea();
    void setupSettingArea();
    void setupConnections();

private slots:
    void changeAvatar();
    void changeUsername();
    void updateAvatarDisplay(const QPixmap &newAvatar);
    void updateUsernameDisplay(const QString &newUsername);
    void expandSettings();
    void addNewSetting();
    void userSettings();

private:
    QHBoxLayout *m_mainLayout;
    QWidget *m_sideArea;
    QStackedLayout *m_settingLayout;

    QPushButton *m_accountButton;
    QPushButton *m_newChatButton;
    QPushButton *m_userButton;

    QLabel *m_avatarLabel;
    QPushButton *m_changeAvatarButton;
    QLineEdit *m_usernameLineEdit;
    QPushButton *m_saveButton;
};

#endif // ISETTINGPAGE_H
