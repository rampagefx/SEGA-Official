#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helpmenu.h"
#include "startgamemenu.h"
#include "filepath.h"
using namespace std;

MainWindow *MainWindow::mutualUi = nullptr;
int MainWindowLength = 1200;
int MainWindowWidth = 800;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mutualUi = this;
    this->setFixedSize(MainWindowLength,MainWindowWidth);   //界面大小设定
    status = 0;
    isBGM = 1;
    QString bgm_dir = bgm_path;
    bgm = new QSound(bgm_dir,this);
    this->setAutoFillBackground(true);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButtonStart_clicked()
{
    status = 1;
    StartGameMenu *new_widget = new StartGameMenu(this);
    new_widget->show();
}
void MainWindow::on_pushButtonHelp_clicked()
{
    status = 5;
    HelpMenu *new_widget = new HelpMenu(this);
    new_widget->show();
}
void MainWindow::on_pushButtonQuit_clicked()
{
    QApplication *quitevent = nullptr;
    quitevent->quit();
}
void MainWindow::on_pushButtonBGM_clicked()
{
    if(isBGM)
    {
        isBGM=0;
        ui->pushButtonBGM->setText("ON");
        bgm->play();
        bgm->setLoops(QSound::Infinite);
    }
    else if(!isBGM)
    {
        isBGM=1;
        ui->pushButtonBGM->setText("OFF");
        bgm->stop();
    }
}
void MainWindow::paintEvent(QPaintEvent *event)
{
    if (status == 0)
    {
        ui->centralwidget->setVisible(true);
        this->setAutoFillBackground(true);
        background.setBrush(QPalette::Background,QBrush(QPixmap(background_pic_path)));
        this->setPalette(background);
    }
    else
    {
        ui->centralwidget->setVisible(false);
    }
}
