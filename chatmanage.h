#ifndef CHATMANAGE_H
#define CHATMANAGE_H

#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QHostAddress>
#include "chatmodel.h"
#include "clientsocket.h"
#include "packet.h"

class ChatManage : public QObject
{
    Q_OBJECT
public:
    explicit ChatManage(QObject *parent = nullptr);
    ChatModel& chatmodel() const { return *(m_chatModel); }

signals:

public slots:
    void sendMessage(QString msg);
    QString getMessage();
    void addChatMessage(const Packet& packet);

private:
    QString message;
    ChatModel* m_chatModel;
    ClientSocket* m_sock;
};

#endif // CHATMANAGE_H
