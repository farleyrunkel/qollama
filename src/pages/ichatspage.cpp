#include "ichatspage.h"
#include "iconfigmanager.h"
#include <QIcon>

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

    mainLayout->addWidget(new ILineEdit);
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

