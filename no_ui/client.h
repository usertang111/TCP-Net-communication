#ifndef CLIENT_H
#define CLIENT_H
#include <QTcpSocket>
#include <QTcpServer>
#include <QObject>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

public slots:
    void connectToServer();
    void sendMessage();
signals:
    void sendHello(); // 用于触发发送消息

private:
    QTcpSocket *m_socket;


};

#endif // CLIENT_H
