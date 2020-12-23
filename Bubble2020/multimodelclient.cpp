#include "multimodelclient.h"
#include "ui_multimodelclient.h"


MultiModelClient::MultiModelClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultiModelClient)
{
    ui->setupUi(this);
    sClient = new SocketClient();
}

MultiModelClient::~MultiModelClient()
{
    delete ui;
}

void MultiModelClient::on_link_start_clicked()
{
    //初始化socket client对象
    QString ip = ui->lineEdit->text();
    int port = ui->lineEdit_2->text().toInt();
    sClient->ClientInit(ip, port);
    //关联开始信号与新游戏的开始
    connect(sClient, SIGNAL(StartGame()), this, SLOT(NewGame()));
}

void MultiModelClient::NewGame()
{
    int opChrt = sClient->recvMsg.at(1).unicode()-'0';
    int myChrt = sClient->recvMsg.at(2).unicode()-'0';
    m = new multigame(myChrt,opChrt,nullptr,sClient);
    this->close();
    m->show();
}
