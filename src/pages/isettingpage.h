#ifndef ISETTINGPAGE_H
#define ISETTINGPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QPixmap>

/**
 * @class ISettingPage
 * @brief Setting page widget
 */
class ISettingPage : public QWidget {
    Q_OBJECT

public:
    explicit ISettingPage(QWidget *parent = nullptr);

private:
    void setupUi();
    void setupConnections();

private slots:
    void changeAvatar();
    void changeUsername();
    void updateAvatarDisplay(const QPixmap &newAvatar);
    void updateUsernameDisplay(const QString &newUsername);

private:
    QVBoxLayout *mainLayout;
    QLabel *avatarLabel;
    QPushButton *changeAvatarButton;
    QLineEdit *usernameLineEdit;
    QPushButton *saveButton;
};

#endif // ISETTINGPAGE_H
