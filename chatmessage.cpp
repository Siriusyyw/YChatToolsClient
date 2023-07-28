#include "chatmessage.h"

ChatMessage::ChatMessage(QObject *parent)
    : QObject{parent}
{

}

ChatMessage::ChatMessage(const ChatMessage &other)
    : QObject(other.parent())
    , m_sender(other.m_sender)
    , m_message(other.m_message)
    , m_timestamp(other.m_timestamp)
    , m_avatarUrl(other.m_avatarUrl)
{

}

ChatMessage &ChatMessage::operator=(const ChatMessage &other)
{
    if (this != &other) {
        m_sender = other.m_sender;
        m_message = other.m_message;
        m_timestamp = other.m_timestamp;
        m_avatarUrl = other.m_avatarUrl;
    }
    return *this;
}

void ChatMessage::setSender(const QString &sender)
{
    if (m_sender != sender) {
        m_sender = sender;
        emit senderChanged();
    }
}

void ChatMessage::setMessage(const QString &message)
{
    if (m_message != message) {
        m_message = message;
        emit messageChanged();
    }
}

void ChatMessage::setTimestamp(const QDateTime &timestamp)
{
    if (m_timestamp != timestamp) {
        m_timestamp = timestamp;
        emit timestampChanged();
    }
}

void ChatMessage::setAvatarUrl(const QUrl &avatarUrl)
{
    if (m_avatarUrl != avatarUrl) {
        m_avatarUrl = avatarUrl;
        emit avatarUrlChanged();
    }
}
