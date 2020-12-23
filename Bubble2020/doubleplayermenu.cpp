#include "doubleplayermenu.h"
#include "ui_doubleplayermenu.h"
#include "doublegame.h"
#include <QDebug>

DoublePlayerMenu::DoublePlayerMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoublePlayerMenu)
{
    player1_status = 0;
    player2_status = 0;
    ui->setupUi(this);
    if (!MainWindow::mutualUi->isBGM)
        ui->pushButtonBGMsingle->setText("ON");
    else
        ui->pushButtonBGMsingle->setText("OFF");
    ui->pushButtonDecide->setVisible(false);
    ui->pushButtonNotDecide1->setVisible(false);
    ui->pushButtonNotDecide2->setVisible(false);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

DoublePlayerMenu::~DoublePlayerMenu()
{
    delete ui;
}
void DoublePlayerMenu::on_pushButtonBackchoose_clicked()
{
    MainWindow::mutualUi->status = 1;
    this->close();
}
void DoublePlayerMenu::on_pushButtonBGMsingle_clicked()
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
void DoublePlayerMenu::on_pushButtonNotDecide1_clicked()
{
    ui->pushButtonDecide->setVisible(false);
    ui->pushButtonCharacter1_1->setVisible(true);
    ui->pushButtonNotDecide1->setVisible(false);
    ui->pushButtonCharacter1_2->setVisible(true);
    ui->pushButtonCharacter1_3->setVisible(true);
    repaint();
}
void DoublePlayerMenu::on_pushButtonNotDecide2_clicked()
{
    ui->pushButtonDecide->setVisible(false);
    ui->pushButtonCharacter2_1->setVisible(true);
    ui->pushButtonNotDecide2->setVisible(false);
    ui->pushButtonCharacter2_2->setVisible(true);
    ui->pushButtonCharacter2_3->setVisible(true);
    repaint();
}
void DoublePlayerMenu::on_pushButtonDecide_clicked()
{
    int q[2] = {player1_status,player2_status};
    DoubleGame *newgame = new DoubleGame(q, nullptr);
    newgame->show();
}
void DoublePlayerMenu::on_pushButtonCharacter1_1_clicked()
{
    player1_status = 0;
    ui->pushButtonNotDecide1->setVisible(true);
    ui->pushButtonCharacter1_2->setVisible(false);
    ui->pushButtonCharacter1_3->setVisible(false);
    repaint();
}
void DoublePlayerMenu::on_pushButtonCharacter1_2_clicked()
{
    player1_status = 1;
    ui->pushButtonNotDecide1->setVisible(true);
    ui->pushButtonCharacter1_1->setVisible(false);
    ui->pushButtonCharacter1_3->setVisible(false);
    repaint();
}
void DoublePlayerMenu::on_pushButtonCharacter1_3_clicked()
{
    player1_status = 2;
    ui->pushButtonNotDecide1->setVisible(true);
    ui->pushButtonCharacter1_2->setVisible(false);
    ui->pushButtonCharacter1_1->setVisible(false);
    repaint();
}
void DoublePlayerMenu::on_pushButtonCharacter2_1_clicked()
{
    player2_status = 0;
    ui->pushButtonNotDecide2->setVisible(true);
    ui->pushButtonCharacter2_2->setVisible(false);
    ui->pushButtonCharacter2_3->setVisible(false);
    repaint();
}
void DoublePlayerMenu::on_pushButtonCharacter2_2_clicked()
{
    player2_status = 1;
    ui->pushButtonNotDecide2->setVisible(true);
    ui->pushButtonCharacter2_1->setVisible(false);
    ui->pushButtonCharacter2_3->setVisible(false);
    repaint();
}
void DoublePlayerMenu::on_pushButtonCharacter2_3_clicked()
{
    player2_status = 2;
    ui->pushButtonNotDecide2->setVisible(true);
    ui->pushButtonCharacter2_2->setVisible(false);
    ui->pushButtonCharacter2_1->setVisible(false);
    repaint();
}
void DoublePlayerMenu::paintEvent(QPaintEvent *event)
{
    if(ui->pushButtonNotDecide2->isVisible() && ui->pushButtonNotDecide1->isVisible())
    {
        ui->pushButtonDecide->setVisible(true);
    }
}
