#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QMessageBox>

class SocketClient : public QWidget
{
    Q_OBJECT

public:
    SocketClient();
    QTcpSocket* mp_clientSocket;
    QString recvMsg;

public slots:
    void ClientInit(QString ip, int port);
    void ClientRecvData();
    void ClientSendData(QString sendMsg);

signals:
    void StartGame();
};

#endif // SOCKETCLIENT_H
