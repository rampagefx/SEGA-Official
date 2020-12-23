#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>

class SocketServer : public QWidget
{
    Q_OBJECT

public:
    SocketServer();
    QTcpServer *mp_TcpServer;
    QTcpSocket *mp_TcpSocket;
    QString recvMsg;

public slots:
    void ServerInit(int port);
    void ServerNewConnection();
    void ServerRecvData();
    void ServerDisConnection();
    void ServerSendData(QString sendMsg);
};
#endif // SOCKETSERVER_H
