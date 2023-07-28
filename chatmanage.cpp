#include "chatmanage.h"

ChatManage::ChatManage(QObject *parent)
    : QObject{parent}
{
    m_chatModel = new ChatModel(this);
    m_sock = new ClientSocket("127.0.0.1", 10246,this);
    connect(m_sock,SIGNAL(chatMessagePacket(Packet)),this,SLOT(addChatMessage(Packet)));
}

void ChatManage::sendMessage(QString msg)
{
    Packet packet(Packet::ChatMessageRequest,msg.toUtf8());
    m_sock->sendMsg(packet);
}

QString ChatManage::getMessage()
{
    return message;
}

void ChatManage::addChatMessage(const Packet &packet)
{
    qDebug() << __LINE__ << __FUNCTION__ << QString(packet.data());
    ChatMessage chatMessage;
    chatMessage.setSender("Alice");
    chatMessage.setMessage(packet.data());
    chatMessage.setTimestamp(QDateTime::currentDateTime());
    chatMessage.setAvatarUrl(QUrl("https://pic.imgdb.cn/item/6380bf7d16f2c2beb106f074.jpg"));
    m_chatModel->addMessage(chatMessage);
}
