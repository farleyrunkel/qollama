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
    explicit ISettingPage(QWidget *parent = nullptr);

protected:
    void showEvent(QShowEvent *) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void setupMainUi();
    void setupSideArea();
    void setupConnections();
    QGroupBox *addSettingGroupBox(const QString &key, const QString &value, const QString &config = "");
    void setupSettingsAccount(QLayout *layout);

private slots:
    void changeAvatar();

private:
    QHBoxLayout *m_mainLayout;
    QWidget *m_sideArea;
    QStackedLayout *m_settingLayout;

    QPushButton *m_avatarButton;

    QMap<QString, QWidget*> m_settings;
};

#endif // ISETTINGPAGE_H
