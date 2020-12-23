 #ifndef MULTIGAME_H
#define MULTIGAME_H

#include <QMainWindow>
#include <QWidget>
#include "singlegame.h"
#include "gamedisplay.h"
#include "socketclient.h"
#include "socketserver.h"
#include <QTimer>

namespace Ui {
class multigame;
}

class multigame : public QMainWindow
{
    Q_OBJECT

public:
    explicit multigame(int myChrt,int opChrt,SocketServer* sServer,SocketClient* sClient,QWidget *parent = nullptr);
    ~multigame();
//    QWidget* hostwidget;
    SocketClient* sClient;
    SocketServer* sServer;
    SingleGame* hostGame;
    GameDisplay* clientGame;
    QTimer* timer;
    int isServer = -1;
public slots:
    void sendAndRecv();

private:
    Ui::multigame *ui;
};

#endif // MULTIGAME_H
