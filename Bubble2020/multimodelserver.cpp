#include "multimodelserver.h"
#include "ui_multimodelserver.h"
#include <QtNetwork>
#include <QMessageBox>
#include "socketserver.h"


MultiModelServer::MultiModelServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultiModelServer)
{
    ui->setupUi(this);
    QString ip = "自动查询错误，请手动查询";
    //查询本机ip
    QString localHostName = QHostInfo::localHostName();

    qDebug() <<"localHostName:"<<localHostName;
    QHostInfo info = QHostInfo::fromName(localHostName);
    foreach(QHostAddress address,info.addresses())
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
        {
            qDebug() <<"IPV4 Address: "<< address.toString();
            ip = address.toString();
        }

    }
    ui->ip_Browser->setText(ip);
    sServer[0] = new SocketServer();
    sServer[0]->ServerInit(sPort[0]);
    QString pS;
    ui->port_Browser->setText("玩家1:"+pS.asprintf("%d",sPort[0]));

}

MultiModelServer::~MultiModelServer()
{
    delete ui;
}

void MultiModelServer::on_creat_server_clicked()
{
    if(clientNum<4){
        sServer[clientNum] = new SocketServer();
        sServer[clientNum]->ServerInit(sPort[clientNum]);
        clientNum++;
        QString pS;
        ui->port_Browser->append("玩家"+pS.asprintf("%d",clientNum)+":"+pS.asprintf("%d",sPort[clientNum-1]));
    }
    else{
        QMessageBox::information(this, "错误","玩家数量已达上限！");
    }
}

void MultiModelServer::on_multi_start_game_clicked()
{
    //  server向client发送开始信息
    QTime* startTime = new QTime();
    QString strTime = startTime->currentTime().toString("hh:mm:ss");
    if(!sServer[0]->mp_TcpSocket){
        QMessageBox::information(this,"错误","无玩家加入");
        return;
    }
    //生成俩随机数
    qsrand(startTime->msec()+startTime->second()*1000);
    int myChrt = qrand()%3;
    int opChrt = qrand()%3;
    QString strStart = "s";
    strStart.append('0'+myChrt);
    strStart.append('0'+opChrt);
    sServer[0]->ServerSendData(strStart);
    m  = new multigame(myChrt,opChrt,sServer[0], nullptr, nullptr);
    this->close();
    m->show();

}



