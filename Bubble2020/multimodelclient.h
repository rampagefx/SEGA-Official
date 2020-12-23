#ifndef MULTIMODELCLIENT_H
#define MULTIMODELCLIENT_H

#include <QWidget>
#include "socketclient.h"
#include <QTime>
#include <QTimer>
#include "multigame.h"

namespace Ui {
class MultiModelClient;
}

class MultiModelClient : public QWidget
{
    Q_OBJECT

public:
    explicit MultiModelClient(QWidget *parent = nullptr);
    ~MultiModelClient();
    SocketClient* sClient;
    int map[12]={1,0,0,0,0,0,0,0,0,0,0,0};
    QTimer *timer;
    multigame* m;

private slots:
    void on_link_start_clicked();
    void NewGame();

private:
    Ui::MultiModelClient *ui;
};

#endif // MULTIMODELCLIENT_H
