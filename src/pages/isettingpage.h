#ifndef ISETTINGPAGE_H
#define ISETTINGPAGE_H

#include <QFileDialog>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class ISettingPage : public QWidget {
    Q_OBJECT

public:
    explicit ISettingPage(QWidget *parent = nullptr);

private:
    void setupMainLayout();
    void setupTopArea();
    void setupSettingArea();
    void setupConnections();
    QPushButton *createButton(const QString &iconPath);

private slots:
    void changeAvatar();
    void changeUsername();
    void updateAvatarDisplay(const QPixmap &newAvatar);
    void updateUsernameDisplay(const QString &newUsername);
    void expandSettings();
    void addNewSetting();
    void userSettings();

private:
    QVBoxLayout *m_mainLayout;
    QWidget *m_topArea;
    QVBoxLayout *m_settingLayout;

    QPushButton *m_expandButton;
    QPushButton *m_newChatButton;
    QPushButton *m_userButton;

    QLabel *m_avatarLabel;
    QPushButton *m_changeAvatarButton;
    QLineEdit *m_usernameLineEdit;
    QPushButton *m_saveButton;
};

#endif // ISETTINGPAGE_H
