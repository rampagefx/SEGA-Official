#ifndef MULTIMODELSERVER_H
#define MULTIMODELSERVER_H

#include <QWidget>
#include <QMessageBox>
#include "socketserver.h"
#include <QTime>
#include <QTimer>
#include "multigame.h"

namespace Ui {
class MultiModelServer;
}

class MultiModelServer : public QWidget
{
    Q_OBJECT

public:
    explicit MultiModelServer(QWidget *parent = nullptr);
    ~MultiModelServer();
    //玩家服务端，最多4个
    SocketServer* sServer[4];
    //对应4个端口号
    int sPort[4] = {5354, 5050, 4747, 8282};
    //当前创建玩家数量
    int clientNum=1;
    int map[12]={2,0,0,0,0,0,0,0,0,0,0,0};
    QTimer *timer;
    multigame* m;


private slots:
    void on_creat_server_clicked();

    void on_multi_start_game_clicked();

private:
    Ui::MultiModelServer *ui;
};

#endif // MULTIMODELSERVER_H
