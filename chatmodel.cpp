#include "chatmodel.h"


ChatModel::ChatModel(QObject* parent)
    : QAbstractListModel{parent}
{

}

int ChatModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_chatMessages.count();
}

QVariant ChatModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_chatMessages.count())
        return QVariant();
    const ChatMessage &message = m_chatMessages.at(index.row());
    switch (role) {
    case SenderRole:
        return message.sender();
    case MessageRole:
        return message.message();
    case TimestampRole:
        return message.timestamp();
    case AvatarUrlRole:
        return message.avatarUrl();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ChatModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[SenderRole] = "sender";
    names[MessageRole] = "message";
    names[TimestampRole] = "timestamp";
    names[AvatarUrlRole] = "avatarUrl";
    return names;
}

void ChatModel::addMessage(const ChatMessage &message)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_chatMessages.append(message);
    endInsertRows();
}

void ChatModel::clearMessages()
{
    beginResetModel();
    m_chatMessages.clear();
    endResetModel();
}
