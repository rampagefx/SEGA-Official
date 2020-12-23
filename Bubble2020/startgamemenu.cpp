#include "startgamemenu.h"
#include "ui_startgamemenu.h"
#include "singleplayermenu.h"
#include "multiplayermenu.h"
#include "doubleplayermenu.h"
#include "doublegame.h"

StartGameMenu::StartGameMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartGameMenu)
{
    ui->setupUi(this);
    if (!MainWindow::mutualUi->isBGM)
        ui->pushButtonBGMstart->setText("ON");
    else
        ui->pushButtonBGMstart->setText("OFF");
    this->setAttribute(Qt::WA_DeleteOnClose);
}

StartGameMenu::~StartGameMenu()
{
    delete ui;
}


void StartGameMenu::on_pushButtonBGMstart_clicked()
{
    if(MainWindow::mutualUi->isBGM)
    {
        MainWindow::mutualUi->isBGM=0;
        ui->pushButtonBGMstart->setText("ON");
        MainWindow::mutualUi->bgm->play();
        MainWindow::mutualUi->bgm->setLoops(QSound::Infinite);
    }
    else if(!MainWindow::mutualUi->isBGM)
    {
        MainWindow::mutualUi->isBGM=1;
        ui->pushButtonBGMstart->setText("OFF");
        MainWindow::mutualUi->bgm->stop();
    }
}
void StartGameMenu::on_pushButtonBackstart_clicked()
{
    MainWindow::mutualUi->status = 0;
    this->close();
}
void StartGameMenu::on_pushButtonMulti_clicked()
{
    MainWindow::mutualUi->status = 4;
    multiplayermenu *new_widget = new multiplayermenu(this);
    new_widget->show();
}
void StartGameMenu::on_pushButtonSingle_clicked()
{
    MainWindow::mutualUi->status = 2;
    SinglePlayerMenu *new_widget = new SinglePlayerMenu(this);
    new_widget->show();
}
void StartGameMenu::on_pushButtonDouble_clicked()
{
    MainWindow::mutualUi->status = 3;
    DoublePlayerMenu *new_widget = new DoublePlayerMenu(this);
    new_widget->show();
}
void StartGameMenu::paintEvent(QPaintEvent *event)
{
    if (MainWindow::mutualUi->status == 1)
    {
        ui->gametitle->setVisible(true);
        ui->pushButtonMulti->setVisible(true);
        ui->pushButtonSingle->setVisible(true);
        ui->pushButtonDouble->setVisible(true);
        ui->BGMTextstart->setVisible(true);
        ui->pushButtonBGMstart->setVisible(true);
        ui->pushButtonBackstart->setVisible(true);
    }
    else
    {
        ui->gametitle->setVisible(false);
        ui->pushButtonMulti->setVisible(false);
        ui->pushButtonSingle->setVisible(false);
        ui->pushButtonDouble->setVisible(false);
        ui->BGMTextstart->setVisible(false);
        ui->pushButtonBGMstart->setVisible(false);
        ui->pushButtonBackstart->setVisible(false);
    }
}
