#include "server.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QString>
Server::Server(QObject *parent) : QTcpServer(parent)
{
    // 连接服务器的 newConnection 信号到 onNewConnection 槽
     connect(this, &QTcpServer::newConnection, this, &Server::onNewConnection);
    // 启动服务器监听
     if (!listen(QHostAddress::Any, 1334)) {
         qDebug() << "Server failed to start:" << errorString();
     } else {
         qDebug() << "Server started on port 1334";
     }
}

void Server::onNewConnection()
{
    // 为新的连接创建 QTcpSocket
    QTcpSocket *nextConn = nextPendingConnection();
    connect(nextConn, &QTcpSocket::readyRead, [this, nextConn]() {
        QString data = nextConn->readAll();
        qDebug() << "Server received:" << data;
        // 发送确认消息回客户端
        nextConn->write("I have receive");
    });
    connect(nextConn, &QTcpSocket::disconnected, [this, nextConn]() {
        m_connections.removeAll(nextConn); // 确保不会重复删除
        nextConn->deleteLater();
    });
    m_connections.append(nextConn);
}
