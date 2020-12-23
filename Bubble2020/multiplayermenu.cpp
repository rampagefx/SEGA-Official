#include "multiplayermenu.h"
#include "ui_multiplayermenu.h"
#include "multimodelserver.h"
#include "ui_multimodelserver.h"
#include "multimodelclient.h"
#include "ui_multimodelclient.h"


multiplayermenu::multiplayermenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::multiplayermenu)
{
    ui->setupUi(this);
}

multiplayermenu::~multiplayermenu()
{
    delete ui;
}

void multiplayermenu::on_creatgame_clicked()
{
    MultiModelServer* serverwidget = new MultiModelServer;
//    this->hide();
    serverwidget->show();
}

void multiplayermenu::on_joingame_clicked()
{
    MultiModelClient* clientwidget = new MultiModelClient;
//    this->hide();
    clientwidget->show();
}

void multiplayermenu::on_multiback_clicked()
{
    MainWindow::mutualUi->status = 1;
    this->close();
}
