#include "server.h"
#include "ui_server.h"
#include <QTcpServer>
#include <QHostAddress>
#include <QDebug>
#include <QDateTime>
#include <QByteArray>
Server::Server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);
    //设置clicked(bool checked)点击反转状态打开
    ui->startorstop_Listen->setCheckable(true);

    socket = new QTcpSocket();
    server = new QTcpServer();

    //信号：新的客户端连接建立 槽函数：获取客户端套接字，允许写入数据
    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection_SLOT()));
}

Server::~Server()
{
    delete ui;
}

//信号：新的客户端连接建立 槽函数：获取客户端套接字，允许写入数据
void Server::newConnection_SLOT()
{
    socket = server->nextPendingConnection(); //获取已经连接的客户端套接字
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead_SLOT()));//如果socket中有缓存消息，触发槽函数
}

//接收消息并显示到接收框
void Server::readyRead_SLOT()
{
    QByteArray data = socket->readAll();
    QString receivedData = QString::fromUtf8(data);
    // 假设时间戳和消息内容之间用空格分隔
    int spaceIndex = receivedData.indexOf(" ");
    QString buffer;
    //读取缓冲区数据
    if (spaceIndex != -1) {
        QString timeStamp = receivedData.left(spaceIndex);
        QString message = receivedData.mid(spaceIndex + 1);

        // 显示时间戳和消息
        qDebug() << "Server Client Received at: " << timeStamp << "Message: " << message;
        // 使用appendHtml来添加带颜色的消息
        // 这里设置消息颜色为红色
        ui->receiver->appendHtml(QString::fromLatin1("<font color='red'>%1</font>").arg(message));
    }
}


//开始监听和停止监听按键
void Server::on_startorstop_Listen_clicked(bool checked)
{
    if(checked)
    {
        int port = ui->portnum->text().toUInt();
        //如果未监听到
        if(!server->listen(QHostAddress::Any, port))
        {
            qDebug() << server->errorString();
            //连接失败，再次点击则重新连接，将checked恢复为true
            ui->startorstop_Listen->toggle();
            return;
        }
        qDebug() << "Listen Successfully! Message from port:" << port;

        //修改按钮文字
        ui->startorstop_Listen->setText("停止监听");
        //发送键使能
        ui->send_button->setEnabled(true);
    }
    else
    {
         qDebug() << "Stop Listening!";
        //如果已经连接则断开连接
        if(socket->state() == QAbstractSocket::ConnectedState)
        {
            //断开连接
            socket->disconnectFromHost();
        }
        //关闭倾听服务
        server->close();
        //修改按钮文字&发送键静默
        ui->startorstop_Listen->setText("开始监听");
        ui->send_button->setEnabled(false);
    }
}

//发送消息，写入socket缓存区
void Server::on_send_button_clicked()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString timeString = currentDateTime.toString("yyyy-MM-dd HH:mm:ss"); // 格式化时间
    QString message = ui->sender->toPlainText();
    QString messages = timeString + " " + message;
    if(!message.isEmpty())
        qDebug() << "Server Send: " << messages;
    else
        qDebug() <<"receive nothing";
    //将输入框的内容写入socket缓冲区
    socket->write(messages.toUtf8());
    //刷新socket缓冲区
    socket->flush();
    ui->sender->clear(); // 清空发送框
}
