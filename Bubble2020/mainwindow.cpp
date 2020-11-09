#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helpmenu.h"
#include "startgamemenu.h"
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
    #ifdef _WIN64
        QString bgm_dir = QCoreApplication::applicationFilePath() + "/music/menu.wav";
        bgm = new QSound(bgm_dir,this);
    #elif __APPLE__
        QString bgm_dir = QCoreApplication::applicationFilePath().section('/',0,-6) + "/music/menu.wav";
        bgm = new QSound(bgm_dir,this);
    #endif
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
        background.setBrush(QPalette::Background,QBrush(QPixmap(QCoreApplication::applicationFilePath().section('/',0,-6) + "/img/menu.jpeg")));
        this->setPalette(background);
    }
    else
    {
        ui->centralwidget->setVisible(false);
    }
}
