#include "socketserver.h"
#include <QMessageBox>

SocketServer::SocketServer()
{

}

// 根据端口初始化server
void SocketServer::ServerInit(int port)
{
    mp_TcpServer = new QTcpServer();
    if (!mp_TcpServer->listen(QHostAddress::Any, port)){
        QMessageBox::information(this, "联网游戏", "服务器端监听失败");
        return;
    }
    else{
        QMessageBox::information(this, "联网游戏", "服务器端监听成功");
        connect(mp_TcpServer, SIGNAL(newConnection()), this, SLOT(ServerNewConnection()));
    }
}

// 建立连接
void SocketServer::ServerNewConnection()
{
    mp_TcpSocket = mp_TcpServer->nextPendingConnection();
    if (!mp_TcpSocket){
        QMessageBox::information(this, "联网游戏", "未正确获取客户端连接！");
        return;
    }
    else{
        QMessageBox::information(this, "联网游戏", "成功接受客户端的连接");
        connect(mp_TcpSocket, SIGNAL(readyRead()), this, SLOT(ServerRecvData()));
        connect(mp_TcpSocket, SIGNAL(disconnected()), this, SLOT(sServerDisConnection()));
    }
}

// server接收数据
void SocketServer::ServerRecvData()
{
    char buf[1024]={0};
    mp_TcpSocket->read(buf, 1024);
    if( strlen(buf) < 0){
        //QMessageBox::information(this, "联网游戏", "未正确接收数据");
        return;
    }
    recvMsg.clear();
    recvMsg = buf;
}

// server发送 qstring型数据
void SocketServer::ServerSendData(QString sendMsg)
{
    char buf[1024]={0};
    strcpy_s(buf, sendMsg.toStdString().c_str());
    int sendFlag = mp_TcpSocket->write(buf, strlen(buf));
    if(sendFlag == -1){
         //QMessageBox::information(this, "联网游戏", "向服务端发送数据失败！");
     }
    return;
}

// 断开连接
void SocketServer::ServerDisConnection()
{
    QMessageBox::information(this, "QT网络通信", "与客户端的连接断开");
    return;
}
