#include "server.h"
#include "client.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server w1;
    Client w2;
    w1.setWindowTitle("通信-服务器");
    w1.setFixedSize(640,400);
    w2.setWindowTitle("通信-客户端");
    w2.setFixedSize(640,400);
    //Client窗口通过鼠标单机获得聚焦
    w2.setFocusPolicy(Qt::ClickFocus);
    //将客户端和服务端窗口移动到屏幕合适位置
    w1.move(320,340);
    w2.move(960,340);

    //打开客户端和服务端窗口
    w1.show();
    w1.activateWindow();
    w2.show();

    return a.exec();
}
