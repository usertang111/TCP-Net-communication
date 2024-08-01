#ifndef SENDFILE_H
#define SENDFILE_H
#include <QTcpSocket>
#include <QObject>

class SendFile : public QObject
{
    Q_OBJECT
public:
    explicit SendFile(QObject *parent = nullptr);

    //连接服务器
    void connectServer(unsigned short port, QString ip);


    //发送文件
    void sendFile(QString path);
signals:
    void connectOK();
    void gameover();
    void curPersent(int num);
private:
    QTcpSocket * m_tcp;
};

#endif // SENDFILE_H
