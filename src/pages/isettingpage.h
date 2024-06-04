#ifndef ISETTINGPAGE_H
#define ISETTINGPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>

class ISettingPage : public QWidget
{
    Q_OBJECT

public:
    explicit ISettingPage(QWidget *parent = nullptr);

private slots:
    void changeAvatar();
    void changeUsername();
    void updateAvatarDisplay(const QPixmap& newAvatar);
    void updateUsernameDisplay(const QString& newUsername);

private:
    QVBoxLayout* mainLayout;
    QLabel* avatarLabel;
    QPushButton* changeAvatarButton;
    QLineEdit* usernameLineEdit;
    QPushButton* saveButton;

    void setupUi();
    void setupConnections();
};

#endif // ISETTINGPAGE_H
