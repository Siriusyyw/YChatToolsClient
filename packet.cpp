#include "packet.h"

Packet::Packet()
{

}

Packet::Packet(const QByteArray &data)
{
    fromByteArray(data);
}

Packet::Packet(PacketType type, const QByteArray &message)
{
    setType(type);
    setMessage(message);
}

QByteArray Packet::toByteArray() const
{
    QByteArray data;
    QByteArray encryptData = encrypt(m_data);
    QDataStream stream(&data, QIODevice::WriteOnly);
    int lenght = encryptData.size() + 12;
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << qint16(0xFFEF);
    stream << qint16(m_type);
    stream << qint32(lenght);
    stream << encryptData;
    stream << qint32(checksum(m_data));
    return data;
}

void Packet::fromByteArray(const QByteArray &data)
{
    QDataStream stream(data);
    stream.setByteOrder(QDataStream::LittleEndian);
    qint16 magic,type;
    stream >> magic >> type;
    if (magic != qint16(0xFFEF))
        qDebug() << __LINE__ << __FUNCTION__ << "Invalid packet header";
    m_type = static_cast<PacketType>(type);
    qint32 packetlen,datalen;
    stream >> packetlen >> datalen;
    if (packetlen != data.size()) {
        qDebug() << __LINE__ << __FUNCTION__ << "Invalid packet length";
        return;
    }
    m_data = decrypt(data.mid(12, datalen));
    qint32 checksum;
    stream >> checksum;
    if (checksum != Packet::checksum(m_data)) {
        qDebug() << __LINE__ << __FUNCTION__ << "Invalid packet checksum";
        return;
    }
}

qint32 Packet::checksum(const QByteArray &data)
{
    qint32 sum = 0;
    for (int i = 0; i < data.size(); i += 2) {
        qint16 value = 0;
        QDataStream stream(data.mid(i, 2));
        stream.setByteOrder(QDataStream::LittleEndian);
        stream >> value;
        sum += value;
    }
    return sum;
}

QByteArray Packet::encrypt(const QByteArray &data)
{
    // Todo:encrypt
    qDebug() << __LINE__ << __FUNCTION__ << "encrypt";
    return data;
}

QByteArray Packet::decrypt(const QByteArray &data)
{
    // Todo:decrypt
    qDebug() << __LINE__ << __FUNCTION__ << "decrypt";
    return data;
}

