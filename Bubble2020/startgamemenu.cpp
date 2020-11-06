#include "startgamemenu.h"
#include "ui_startgamemenu.h"

StartGameMenu::StartGameMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartGameMenu)
{
    ui->setupUi(this);
    if (!MainWindow::mutualUi->isBGM)
        ui->pushButtonBGMstart->setText("ON");
    else
        ui->pushButtonBGMstart->setText("OFF");
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
}
void StartGameMenu::on_pushButtonSingle_clicked()
{
    MainWindow::mutualUi->status = 2;
}
void StartGameMenu::on_pushButtonDouble_clicked()
{
    MainWindow::mutualUi->status = 3;
}
