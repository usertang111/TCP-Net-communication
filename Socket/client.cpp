#include "client.h"
#include "ui_client.h"
#include "stdio.h"
#include "QString"
#include <QDateTime>
#include <QByteArray>

Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    //设置clicked(bool checked)点击反转状态打开
    ui->connect_button->setCheckable(true);

    socket = new QTcpSocket();

    //信号：客户端申请连接成功 槽函数：允许写入数据
    connect(socket,SIGNAL(connected()),this,SLOT(connected_SLOT()));
}

Client::~Client()
{
    delete ui;
}

//信号：客户端申请连接成功 槽函数：允许写入数据
void Client::connected_SLOT()
{
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead_SLOT()));//如果socket中有缓存消息，触发槽函数
}

//接收消息并显示到接收框
void Client::readyRead_SLOT()
{
    QByteArray data = socket->readAll();
    QString receivedData = QString::fromUtf8(data);
    // 假设时间戳和消息内容之间用空格分隔
    int spaceIndex = receivedData.indexOf(" ");
    //读取缓冲区数据

    if (spaceIndex != -1) {
        QString timeStamp = receivedData.left(spaceIndex);
        QString message = receivedData.mid(spaceIndex + 1);

        // 显示时间戳和消息
        qDebug() << "Client Received at: " << timeStamp << "Message: " << message;
        // 使用appendHtml来添加带颜色的消息
        // 这里设置消息颜色为蓝色
        ui->receiver->appendHtml(QString::fromLatin1("<font color='blue'>%1</font>").arg(message));
    }

}

//连接和断开按键
void Client::on_connect_button_clicked(bool checked)
{
    if(checked)
    {
        QString IP = ui->ipnum->text();
        int Port = ui->portnum->text().toUInt();
        //取消已有的连接
        socket->abort();
        //连接服务器
        socket->connectToHost(IP,Port);
        //如果等待超过1000ms
        if(!socket->waitForConnected(1000))
        {
            qDebug() << "Connect failed, please try again later!";
            //连接失败，再次点击则重新连接，将checked恢复为true
            ui->connect_button->toggle();
            return;
        }
        qDebug() << "Connect Successfully! Connect with IP:" << IP << "; port:" << Port;
        //修改按键文字
        ui->connect_button->setText("断开连接");
        //发送键使能
        ui->send_button->setEnabled(true);

    }
    else
    {
        qDebug() << "Disconnect!";
        //断开连接
        socket->disconnectFromHost();
        //修改按键文字&发送键静默
        ui->connect_button->setText("连接");
        ui->send_button->setEnabled(false);
    }
}

//发送消息，写入socket缓存区
void Client::on_send_button_clicked()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString timeString = currentDateTime.toString("yyyy-MM-dd HH:mm:ss"); // 格式化时间
    QString message =  ui->sender->toPlainText();
    QString messages = timeString + " " + message;
    if(!message.isEmpty())
        qDebug() << "Client Send: " <<messages;
    else
        qDebug() << "receive nothing";
    //将输入框的内容写入socket缓冲区
    socket->write(messages.toUtf8());
    //刷新socket缓冲区
    socket->flush();
    ui->sender->clear();//清空
}


