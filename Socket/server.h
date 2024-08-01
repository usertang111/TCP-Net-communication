#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
QT_END_NAMESPACE

class Server : public QMainWindow
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();

private slots:
    void on_send_button_clicked();

    void on_startorstop_Listen_clicked(bool checked);

    void readyRead_SLOT();

    void newConnection_SLOT();

private:
    Ui::Server *ui;
    QTcpSocket *socket;
    QTcpServer *server;
};
#endif // SERVER_H
