#ifndef CHATBOT_H
#define CHATBOT_H
#include <string>

class ChatBot
{
public:
    ChatBot();

    std::string reply(std::string text = "") {

        return std::string("Echo: " + text);
    }
private:
    std::string label;
};

#endif // CHATBOT_H
