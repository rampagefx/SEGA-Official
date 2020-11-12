#include "helpmenu.h"
#include "ui_helpmenu.h"

HelpMenu::HelpMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpMenu)
{
    ui->setupUi(this);
    if (!MainWindow::mutualUi->isBGM)
        ui->pushButtonBGMhelp->setText("ON");
    else
        ui->pushButtonBGMhelp->setText("OFF");
    ui->pushButtonreturn->setVisible(false);
    ui->IntroText->setVisible(false);
    ui->BackgroundText->setVisible(false);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

HelpMenu::~HelpMenu()
{
    delete ui;
}

void HelpMenu::on_pushButtonBGMhelp_clicked()
{
    if(MainWindow::mutualUi->isBGM)
    {
        MainWindow::mutualUi->isBGM=0;
        ui->pushButtonBGMhelp->setText("ON");
        MainWindow::mutualUi->bgm->play();
        MainWindow::mutualUi->bgm->setLoops(QSound::Infinite);
    }
    else if(!MainWindow::mutualUi->isBGM)
    {
        MainWindow::mutualUi->isBGM=1;
        ui->pushButtonBGMhelp->setText("OFF");
        MainWindow::mutualUi->bgm->stop();
    }
}
void HelpMenu::on_pushButtonBackhelp_clicked()
{
    MainWindow::mutualUi->status = 0;
    this->close();
}
void HelpMenu::on_pushButtonItem_clicked()
{
    ui->pushButtonreturn->setVisible(true);
    ui->pushButtonCharacter->setVisible(false);
    ui->pushButtonIntro->setVisible(false);
    ui->pushButtonBackground->setVisible(false);
    repaint();
}
void HelpMenu::on_pushButtonBackground_clicked()
{
    ui->pushButtonreturn->setVisible(true);
    ui->pushButtonCharacter->setVisible(false);
    ui->pushButtonIntro->setVisible(false);
    ui->pushButtonItem->setVisible(false);
    ui->BackgroundText->setVisible(true);
    repaint();
}
void HelpMenu::on_pushButtonIntro_clicked()
{
    ui->pushButtonreturn->setVisible(true);
    ui->pushButtonCharacter->setVisible(false);
    ui->pushButtonItem->setVisible(false);
    ui->pushButtonBackground->setVisible(false);
    ui->IntroText->setVisible(true);
    repaint();
}
void HelpMenu::on_pushButtonCharacter_clicked()
{
    ui->pushButtonreturn->setVisible(true);
    ui->pushButtonItem->setVisible(false);
    ui->pushButtonIntro->setVisible(false);
    ui->pushButtonBackground->setVisible(false);
    repaint();
}
void HelpMenu::on_pushButtonreturn_clicked()
{
    ui->pushButtonreturn->setVisible(false);
    ui->pushButtonItem->setVisible(true);
    ui->pushButtonCharacter->setVisible(true);
    ui->pushButtonIntro->setVisible(true);
    ui->pushButtonBackground->setVisible(true);
    ui->IntroText->setVisible(false);
    ui->BackgroundText->setVisible(false);
    repaint();
}
