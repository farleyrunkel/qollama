#include "ichatspage.h"
#include "iconfigmanager.h"
#include <QIcon>
#include <QMenu>

IChatsPage::IChatsPage(QWidget *parent): QWidget(parent)
{
    setupUI();

    connect(&ISignalHub::instance(), &ISignalHub::on_IVPushCard_clicked, this, &IChatsPage::sendMessage);
}

void IChatsPage::setupUI() {

    mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    chatsContainer = new QStackedWidget;

    mainLayout->addWidget(chatsContainer);

    lineEdit = new ILineEdit;

    lineEdit = new ILineEdit;
    auto rightButton = lineEdit->rightButton();
    rightButton->setIcon(QIcon(":/icon/send.svg"));

    auto leftButton = lineEdit->leftButton();
    leftButton->setIcon(QIcon("://icon/more-horiz.svg"));

    m_menu = new QMenu;
    leftButton->setMenu(m_menu);
    emit ISignalHub::instance().listRequest();

    connect(&ISignalHub::instance(), &ISignalHub::listReceived, [this](const QList<QString>& list) {
        for (const auto& a : list) {
            auto action = new QAction(a, this);
            m_menu->addAction(action);
            connect(action, &QAction::triggered, this, [this, action]() {
                this->lineEdit->setPlaceholderText("Message " + action->text() + " ...");
            });

            emit action->triggered();
        }
    });

    mainLayout->addWidget(lineEdit);
}

void IChatsPage::sendMessage(const QString &text) {

    if (text.isEmpty()) {return;}

    if (currentChat() == nullptr) {
        addChat();
    }

    currentChat()->addMessage(text, IConfigManager::instance().getUsername(), IConfigManager::instance().getAvatar());
    currentChat()->addMessage("", "llama3");

    QJsonObject json ;
    json["prompt"] = text;
    json["model"] = "llama3";

    emit ISignalHub::instance().generateRequest(json);
}

IChatWidget *IChatsPage::addChat() {
    auto chat  = new IChatWidget;
    chatsContainer->addWidget(chat);

    emit ISignalHub::instance().newChatAdded(chatsContainer->count());

    return chat;
}

IChatWidget *IChatsPage::currentChat() {
    return qobject_cast<IChatWidget*>(chatsContainer->currentWidget());
}

