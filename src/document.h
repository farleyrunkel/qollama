#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "nlohmann/json.hpp"

/*
{
    "label":
    "time":
    "chats":[
        {
        "user":
        "text":
        },
        {
        "user":
        "text":
        }
    ]
}
*/


class Document
{
public:
    Document();


    void addChat(std::string user, std::string text);

private:
    nlohmann::json m_doc;
};

#endif // DOCUMENT_H
