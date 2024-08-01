#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QKeyEvent>
#include <QWidget>

namespace Ui {
class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    ~Client();

private slots:
    void on_connect_button_clicked(bool checked);

    void on_send_button_clicked();

    void readyRead_SLOT();

    void connected_SLOT();

private:
    Ui::Client *ui;
    QTcpSocket *socket;
};

#endif // CLIENT_H
