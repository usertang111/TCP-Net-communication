#ifndef SERVER_H
#define SERVER_H
#include <QTcpSocket>
#include <QObject>
#include <QTcpServer>
#include <QList>
class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
private slots:
    void onNewConnection(); // 处理新的连接

private:
    QTcpServer *m_server; // TCP 服务器
    QList<QTcpSocket*> m_connections; // 存储活动连接
};

#endif // SERVER_H
