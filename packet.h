#ifndef PACKET_H
#define PACKET_H
#include <QDebug>
#include <QDataStream>

class Packet
{
public:
    enum PacketType {
        UnknownType = 0,
        LoginRequest = 1,
        LoginResponse = 2,
        LogoutRequest = 3,
        LogoutResponse = 4,
        ChatMessageRequest = 5,
        ChatMessageResponse = 6,
        // 添加其他包类型
    };
    Packet();
    Packet(const QByteArray &data);
    Packet(PacketType type, const QByteArray &message);
    QByteArray toByteArray() const;
    void fromByteArray(const QByteArray &data);
    void setMessage(const QByteArray &message) { m_data = message;}
    void setType(PacketType type) { m_type = type; }
    QByteArray data() const { return m_data; }
    PacketType type() const { return m_type; }

    static qint32 checksum(const QByteArray &data);
    static QByteArray encrypt(const QByteArray &data);
    static QByteArray decrypt(const QByteArray &data);

private:
    PacketType m_type;
    QByteArray m_data;
};

#endif // PACKET_H
