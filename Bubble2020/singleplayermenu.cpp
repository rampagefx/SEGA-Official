#include "singleplayermenu.h"
#include "ui_singleplayermenu.h"
#include "singlegame.h"
#include <QDebug>
SinglePlayerMenu::SinglePlayerMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SinglePlayerMenu)
{
    ui->setupUi(this);
    if (!MainWindow::mutualUi->isBGM)
        ui->pushButtonBGMsingle->setText("ON");
    else
        ui->pushButtonBGMsingle->setText("OFF");
    ui->textCharacter1->setVisible(false);
    ui->pushButtonDecide->setVisible(false);
    ui->pushButtonNotDecide->setVisible(false);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

SinglePlayerMenu::~SinglePlayerMenu()
{
    delete ui;
}

void SinglePlayerMenu::on_pushButtonBackchoose_clicked()    //返回游戏模式选择
{
    MainWindow::mutualUi->status = 1;
    this->close();
}
void SinglePlayerMenu::on_pushButtonBGMsingle_clicked()     //BGM
{
    if(MainWindow::mutualUi->isBGM)
    {
        MainWindow::mutualUi->isBGM=0;
        ui->pushButtonBGMsingle->setText("ON");
        MainWindow::mutualUi->bgm->play();
        MainWindow::mutualUi->bgm->setLoops(QSound::Infinite);
    }
    else if(!MainWindow::mutualUi->isBGM)
    {
        MainWindow::mutualUi->isBGM=1;
        ui->pushButtonBGMsingle->setText("OFF");
        MainWindow::mutualUi->bgm->stop();
    }
}
void SinglePlayerMenu::on_pushButtonNotDecide_clicked()     //取消选择
{
    ui->textCharacter1->setVisible(false);
    ui->pushButtonDecide->setVisible(false);
    ui->pushButtonNotDecide->setVisible(false);
    ui->pushButtonCharacter2->setVisible(true);
    ui->pushButtonCharacter3->setVisible(true);
    repaint();
}
void SinglePlayerMenu::on_pushButtonDecide_clicked()
{
    //代表选择人物 1
    if (ui->textCharacter1->isVisible())
    {
        int character_choose = 1;
        SingleGame *newgame = new SingleGame(0);
        newgame->show();

    }

        //TODO:
}
void SinglePlayerMenu::on_pushButtonCharacter1_clicked()    //选择角色1
{
    ui->textCharacter1->setVisible(true);
    ui->pushButtonDecide->setVisible(true);
    ui->pushButtonNotDecide->setVisible(true);
    ui->pushButtonCharacter2->setVisible(false);
    ui->pushButtonCharacter3->setVisible(false);
    repaint();
}
void SinglePlayerMenu::on_pushButtonCharacter2_clicked()       //选择角色2
{

}
void SinglePlayerMenu::on_pushButtonCharacter3_clicked()        //选择角色3
{

}
