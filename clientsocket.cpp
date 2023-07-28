#include "clientsocket.h"

ClientSocket::ClientSocket()
    : ClientSocket("127.0.0.1",10246)
{

}

ClientSocket::ClientSocket(QString address, qint64 port, QObject *parent)
    : QObject{parent}
{
    m_socket = new QTcpSocket(this);
    m_address = address;
    m_port = port;
    connect(m_socket,SIGNAL(readyRead()),this,SLOT(readData()));
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(m_socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));

    m_socket->connectToHost(QHostAddress(address), port);
    if(m_socket->waitForConnected())
    {
        qDebug() << "connection to " << address <<" succeeded!";
    }
    else{
        qDebug() << "Connection failed!";
    }
}

ClientSocket::~ClientSocket()
{
    if(m_socket->isValid())
    {
        m_socket->close();
    }
}

void ClientSocket::setAddress(const QString &address)
{
    if (m_address != address)
    {
        m_address = address;
        emit addressChanged();
    }
}

void ClientSocket::setPort(const quint16 port)
{
    if (port <= 65536)
    {
        m_port = port;
        emit portChanged();
    }
}

qint64 ClientSocket::sendMsg(const QString &msgStr)
{
    if(msgStr.isEmpty()) return 0;
    QByteArray data = msgStr.toUtf8();
    qint64 len = m_socket->write(data);
    m_socket->flush();
    return len;
}

qint64 ClientSocket::sendMsg(const QByteArray &msgByte)
{
    if(msgByte.isNull() || msgByte.isEmpty()) return 0;
    qint64 len = m_socket->write(msgByte);
    m_socket->flush();
    return len;
}

qint64 ClientSocket::sendMsg(const Packet &packet)
{
    QByteArray data = packet.toByteArray();
    qDebug() << __LINE__ << __FUNCTION__ << data;
    qint64 len = m_socket->write(data);
    m_socket->flush();
    return len;
}

void ClientSocket::readData()
{
    QByteArray data = m_socket->readAll();
    handleServerData(data);
}

void ClientSocket::displayError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "displayError:" << socketError;

}

void ClientSocket::bytesWritten(qint64 bytes)
{
    qDebug() << "bytesWritten:" << bytes;
}

void ClientSocket::handleServerData(QByteArray &buffer)
{
    QList<Packet>  packets;
    while (!buffer.isEmpty()) {
        // 检查是否有足够的数据读取数据包长度
        if (buffer.size() < 12) {
            break; // 数据不足，等待下一次读取
        }

        // 读取魔数和数据包长度
        QDataStream stream(buffer);
        stream.setByteOrder(QDataStream::LittleEndian);
        qint16 magic,type;
        qint32 packetSize;
        stream >> magic >> type >> packetSize;
        // 检查魔数是否正确
        if (magic != qint16(0xFFEF)) {
            qWarning() << "Invalid magic number";
            buffer.clear();
            break;
        }

        // 检查是否有足够的数据读取整个数据包
        if (buffer.size() < packetSize) {
            break; // 数据不足，等待下一次读取
        }

        // 提取数据包并添加到列表中
        QByteArray packetData = buffer.left(packetSize);
        buffer = buffer.mid(packetSize);
        Packet packet(packetData);
        packets.append(packet);
    }

    // 处理提取出的packet包
    foreach (const Packet &packet, packets) {
        switch (packet.type()) {
        case Packet::UnknownType:
            qDebug() << "Unknown Packet";
            break;
        case Packet::ChatMessageRequest:
            emit chatMessagePacket(packet);
            break;
        default:
            qDebug() << "default Packet";
            break;
        }
    }

}
