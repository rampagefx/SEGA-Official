#include "multigame.h"
#include "singlegame.h"
#include "ui_multigame.h"
#include <QMessageBox>

multigame::multigame(int myChrt, int opChrt,SocketServer* inputServer,SocketClient* inputClient,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::multigame)
{
    ui->setupUi(this);
    hostGame = new SingleGame(myChrt,this);
    hostGame->show();
    clientGame = new GameDisplay(opChrt,this);
    clientGame->show();
    if(inputServer){
        sServer = inputServer;
        isServer = 1;
    }
    else if(inputClient){
        sClient = inputClient;
        isServer = 0;
    }

    // 设置定时器
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(sendAndRecv()));
    timer->start(500);


}

multigame::~multigame()
{
    delete ui;
}

void multigame::sendAndRecv()
{
//    QMessageBox::information(this,"传输","执行传输");
    if(isServer==-1){
        return;
    }
    else if(isServer){
        //int型map转qstring
        int** sendMap;
        sendMap = new int*[map_size_x];
        for(int i =0;i<map_size_x;i++)
        {
            sendMap[i] = new int[map_size_y];
        }
        for (int i=0; i < map_size_x; i++)
            for (int j = 0; j < map_size_y; j++)
            {
                sendMap[i][j] = hostGame->map[i][j];
                //人物位置信息
                if(i==hostGame->player->Get_locationx() && j==hostGame->player->Get_locationy())
                {
                    sendMap[i][j]=ISCHARACTER;
                }
                //NPC位置信息
                for (int k = 0;k < client_enemy_num; k++)
                {
                    if(i==hostGame->enemys[k]->Get_locationx() && j==hostGame->enemys[k]->Get_locationy()){
                           sendMap[i][j]=ISNPC;
                           if(hostGame->enemys[k]->Get_HP()<=0){
                               sendMap[i][j]=NPCDEAD;
                           }
                    }
                }
            }
        QString sendMsg = "";
        for(int i=0;i<map_size_x;i++){
            for(int j=0;j<map_size_y;j++){
                sendMsg.append(sendMap[i][j]+'0');
            }
        }

      //SERVER发送信息
//       QMessageBox::information(this,"传输","执行发送");
       sServer->ServerSendData(sendMsg);

       //SERVER接受信息
       QString recvMsg =  sServer->recvMsg;
       //qstring型map 转int
       int** recvMap;
       recvMap = new int*[map_size_x];
       for(int i =0;i<map_size_x;i++)
       {
           recvMap[i] = new int[map_size_y];
       }
       for (int i=0; i < map_size_x; i++)
           for (int j = 0; j < map_size_y; j++)
               recvMap[i][j] = 0;
       int loopVariable =0;
       if(recvMsg.length()>50){
           while (loopVariable<map_size_x*map_size_y){
               int x = loopVariable/map_size_x;
               int y = loopVariable%map_size_y;
               recvMap[x][y]=recvMsg.at(loopVariable).unicode()-'0';
               loopVariable++;
           }
       }
       //更新gamedisplay
//       QMessageBox::information(this,"传输","执行更新");
       clientGame->MapUpdate(recvMap);
//        QMessageBox::information(this,"传输","地图更新结束");
    }
    else{
        //int型map转qstring
        int** sendMap;
        sendMap = new int*[map_size_x];
        for(int i =0;i<map_size_x;i++)
        {
            sendMap[i] = new int[map_size_y];
        }
        for (int i=0; i < map_size_x; i++)
            for (int j = 0; j < map_size_y; j++)
            {
                sendMap[i][j] = hostGame->map[i][j];
                //人物位置信息
                if(i==hostGame->player->Get_locationx() && j==hostGame->player->Get_locationy())
                {
                    sendMap[i][j]=ISCHARACTER;
                }
                //NPC位置信息
                for (int k = 0;k < client_enemy_num; k++)
                {
                    if(i==hostGame->enemys[k]->Get_locationx() && j==hostGame->enemys[k]->Get_locationy())
                    {
                        sendMap[i][j]=ISNPC;
                        if(hostGame->enemys[k]->Get_HP()==0){
                            sendMap[i][j]=NPCDEAD;
                        }
                    }
                }
            }
        QString sendMsg = "";
        for(int i=0;i<map_size_x;i++){
            for(int j=0;j<map_size_y;j++){
                sendMsg.append(sendMap[i][j]+'0');
            }
        }
        //CLIENT发送信息
        sClient->ClientSendData(sendMsg);

        //CLIENT接受信息
        QString recvMsg = sClient->recvMsg;
        //qstring型map 转int
        int** recvMap;
        recvMap = new int*[map_size_x];
        for(int i =0;i<map_size_x;i++)
        {
            recvMap[i] = new int[map_size_y];
        }
        for (int i=0; i < map_size_x; i++)
            for (int j = 0; j < map_size_y; j++)
                recvMap[i][j] = 0;
        int loopVariable =0;
        if(recvMsg.length()>50){
            while (loopVariable<map_size_x*map_size_y){
                int x = loopVariable/map_size_x;
                int y = loopVariable%map_size_y;
                recvMap[x][y]=recvMsg.at(loopVariable).unicode()-'0';
                loopVariable++;
            }
        }
        //更新gamedisplay
        clientGame->MapUpdate(recvMap);
    }


}
