#include "widget.h"
#include "server.h"
#include "client.h"
#include <QCoreApplication>
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Server server;
    // 检查服务器是否成功启动或已经在监听
    if (!server.isListening()) {
        // 启动服务器监听
        if (!server.listen(QHostAddress::Any, 1334)) {
            qDebug() << "Server failed to start:" << server.errorString();
            return -1;
        }
        qDebug() << "Server started on port 1334";
    } else {
        qDebug() << "成功连接";
    }


    Client client;
    client.connectToServer();

    return app.exec();
}
