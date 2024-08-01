#include "client.h"
#include <QTcpServer>
#include <QCoreApplication>
#include <QDebug>
#include <QTcpSocket>
#include <QString>
Client::Client(QObject *parent) : QObject(parent), m_socket(new QTcpSocket(this)) {
    // 连接信号和槽
    connect(m_socket, &QTcpSocket::connected, this, &Client::sendMessage);
    connect(m_socket, &QTcpSocket::readyRead, [this]() {
        QString data = m_socket->readAll(); // 修正为使用 m_socket
        qDebug() << "Client received:" << data;
        QCoreApplication::instance()->quit();
    });
    connect(m_socket, static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error),
        [this](QTcpSocket::SocketError err) {
                qWarning() << "Client error occurred:" << err;
                // 处理错误，例如关闭socket
                m_socket->close();
                // 或者退出程序
                // QCoreApplication::instance()->quit();
            });
}

void Client::connectToServer()
{
    m_socket->connectToHost("127.0.0.1", 1334);
}

void Client::sendMessage()
{
    const QString message = "Message";
    m_socket->write(message.toUtf8());
}
