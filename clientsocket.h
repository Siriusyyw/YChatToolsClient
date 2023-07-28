#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include "packet.h"

class ClientSocket : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(quint16 port READ port WRITE setPort NOTIFY portChanged)
public:
    explicit ClientSocket();
    explicit ClientSocket(QString address,qint64 port,QObject *parent = nullptr);
    ~ClientSocket();
    void setAddress(const QString &address);
    void setPort(const quint16 port);
    QString address() const { return m_address; }
    quint16 port() const { return m_port; }


signals:
    void addressChanged();
    void portChanged();
    void chatMessagePacket(const Packet& packet);

public slots:
    void readData();
    void displayError(QAbstractSocket::SocketError socketError);
    void bytesWritten(qint64 bytes);
    qint64  sendMsg(const QString& msgStr);
    qint64  sendMsg(const QByteArray& msgByte);
    qint64  sendMsg(const Packet& packet);

private:
    void  handleServerData(QByteArray& msgByte);
private:
    QTcpSocket* m_socket;
    QString m_address;
    quint16 m_port;
};

#endif // CLIENTSOCKET_H
