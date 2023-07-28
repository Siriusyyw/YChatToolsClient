#ifndef CHATMODEL_H
#define CHATMODEL_H

#include <QAbstractListModel>
#include "chatmessage.h"

class ChatModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ChatRoles {
        SenderRole = Qt::UserRole + 1,
        MessageRole,
        TimestampRole,
        AvatarUrlRole
    };
    explicit ChatModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    void addMessage(const ChatMessage &chatMessage);
    void clearMessages();
private:
    QList<ChatMessage> m_chatMessages;
};

#endif // CHATMODEL_H







