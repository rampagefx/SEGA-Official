#include "socketclient.h"

SocketClient::SocketClient()
{

}

// 根据ip与端口，初始化client端
void SocketClient::ClientInit(QString ip, int port)
{
    mp_clientSocket = new QTcpSocket();
    mp_clientSocket->connectToHost(ip,port);
    if (!mp_clientSocket->waitForConnected(30000)){
        QMessageBox::information(this, "联网游戏", "连接服务端失败！");
        return;
    }
    else{
         QMessageBox::information(this, "联网游戏", "连接成功！");
    }
    connect(mp_clientSocket, SIGNAL(readyRead()), this, SLOT(ClientRecvData()));
}

// client接收信息
void SocketClient::ClientRecvData()
{
    char buf[1024]={0};
    mp_clientSocket->read(buf, 1024);
    if(strlen(buf) < 0){
        //QMessageBox::information(this, "联网游戏", "接收服务端数据失败！");
        return;
    }
    recvMsg.clear();
    recvMsg = buf;
    if (recvMsg.at(0).unicode()=='s'){
        emit StartGame();
    }
}

// client发送信息
void SocketClient::ClientSendData(QString sendMsg)
{
   char buf[1024]={0};
   strcpy(buf, sendMsg.toStdString().c_str());
   int sendFlag = mp_clientSocket->write(buf, strlen(buf));
   if(sendFlag == -1){
        //QMessageBox::information(this, "联网游戏", "向服务端发送数据失败！");
    }
   return;
}
