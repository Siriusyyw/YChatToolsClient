#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include <QObject>
#include <QDateTime>
#include <QUrl>

class ChatMessage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString sender READ sender WRITE setSender NOTIFY senderChanged)
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
    Q_PROPERTY(QDateTime timestamp READ timestamp WRITE setTimestamp NOTIFY timestampChanged)
    Q_PROPERTY(QUrl avatarUrl READ avatarUrl WRITE setAvatarUrl NOTIFY avatarUrlChanged)
public:
    explicit ChatMessage(QObject *parent = nullptr);
    ChatMessage(const ChatMessage &other);
    ChatMessage &operator=(const ChatMessage &other);
    void setSender(const QString &sender);
    void setMessage(const QString &message);
    void setTimestamp(const QDateTime &timestamp);
    void setAvatarUrl(const QUrl &avatarUrl);
    QString sender() const { return m_sender; }
    QString message() const { return m_message; }
    QDateTime timestamp() const { return m_timestamp; }
    QUrl avatarUrl() const { return m_avatarUrl; }

signals:
    void senderChanged();
    void messageChanged();
    void timestampChanged();
    void avatarUrlChanged();
private:
    QString m_sender;
    QString m_message;
    QDateTime m_timestamp;
    QUrl m_avatarUrl;
};

#endif // CHATMESSAGE_H
