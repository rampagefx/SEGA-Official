#include "gamedisplay.h"
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QFile>
#include "pikachu.h"
#include "npc.h"
#include "filepath.h"
#include "misaka.h"
#include "peco.h"

using namespace std;
#define PLAYING 0
#define DEAD 1
#define PASS 2
const int CD = 500;
GameDisplay::GameDisplay(int player_id, QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    frame = 0;
    GameStatus = 0;
    resize(client_size_x, client_size_y);
    map = new int*[client_map_size_y];
    for (int i = 0; i < client_map_size_x; ++i)
    {
        map[i] = new int[client_map_size_x];
    }
    for (int i=0; i < client_map_size_y; ++i)
        for (int j = 0; j < client_map_size_x; ++j)
            map[i][j] = 0; // initialize
    MapLoad(0);
    switch (player_id)
    {
    case 0: player = new Pikachu(1, 101, 1, 10, 10); break;
    case 1: player = new Misaka(1, 101, 1, 10, 10); break;
    case 2: player = new Pecoliimu(3, 101, 1, 10, 10); break;
    //default: this->close();
    }
    // Test img read
    for(int i = 0; i < 6; i++)
        map_image[i].load(map_image_path[i]);
    character_image.load(player->pic_path);
//    bomb_image.load(map_image_path[3]);
    enemy_image.load(npc_pic_path);
//    player_image.load(player->big_pic_path);
//    player_profile = new QLabel(this);
//    player_profile->setPixmap(QPixmap::fromImage(player_image));
//    player_profile->setGeometry(750, 50, 200, 200);
//    player_profile->show();
    LabelPicturePause=new QLabel(this);
    // map_pic[j][i] -> setGeometry((i-1)*pic_scale_x+start_point.x(), (j-1)*pic_scale_y+start_point.y(), pic_scale_x, pic_scale_y);
    int count = 0;
    for (int i = 0; i < client_map_size_x; i++)
    {
        for (int j = 0; j < client_map_size_y; j++)
        {
            map_pic[j][i] = new QLabel(this);
            QPixmap pix = QPixmap::fromImage(map_image[0]);
            qreal width = pix.width(); //获得以前图片的宽和高
            qreal height = pix.height();
            pix = pix.scaled(width*scale_ratio,height*scale_ratio,Qt::KeepAspectRatio);
            int pic_scale_x = client_pic_size_x*scale_ratio;
            int pic_scale_y = client_pic_size_y*scale_ratio;
            map_pic[j][i] -> setPixmap(QPixmap::fromImage(map_image[0]));
//            map_pic[j][i] -> setGeometry((i-1)*client_pic_size_x+start_point.x(), (j-1)*client_pic_size_y+start_point.y(), client_pic_size_x, client_pic_size_y);
            map_pic[j][i] -> setGeometry((i-1)*pic_scale_x+start_point.x(), (j-1)*pic_scale_y+start_point.y(), pic_scale_x, pic_scale_y);
            map_pic[j][i] -> setScaledContents(true);
            map_pic[j][i] -> show();
            if (map[j][i] == NPCMAP && count < client_enemy_num)
            {
                enemys[count] = new npc(1, count, NPC, i, j);
                map[j][i] = 0;
                count++;
            }
        }
    }
//    discription[2] = new QLabel(this);
//    discription[2]->setGeometry(775, 275, 200, 100);
//    discription[2]->setText(player->discription);
//    background_image.load(game_background);
//    game_back = new QLabel(this);
//    game_back->setGeometry(0, 0, 1000, 730);
//    game_back->setPixmap(QPixmap::fromImage(background_image));
//    game_back->show();
//    game_back->lower();
//    grabKeyboard();
//    //QKeyEvent *ev;
//    //keyPressEvent(ev);
//    HP_show = new QLCDNumber(this);
//    HP_show->setGeometry(800, 500, 100, 50);
//    CD_display = new QProgressBar(this);
//    CD_display->setMaximum(CD);
//    CD_display->setGeometry(800, 600, 100, 50);
//    CD_display->setValue(CD);
//    CD_display->show();
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
    connect(timer,SIGNAL(timeout()), this, SLOT(frame_plus()));
    timer->start(1);
    setAttribute(Qt::WA_DeleteOnClose);
}

void GameDisplay::paintEvent(QPaintEvent *event)
{
    //qDebug() << "paint";

    QPainter painter;
    int pic_scale_x = client_pic_size_x*scale_ratio;
    int pic_scale_y = client_pic_size_y*scale_ratio;
    for (int i = 0; i < client_map_size_x; i++)
    {
        for (int j = 0; j < client_map_size_y; j++)
        {
            if (map[j][i] == 0)
            {
                int tmp = 0;
                map_pic[j][i] -> setPixmap(QPixmap::fromImage(map_image[tmp]));
                map_pic[j][i] -> setGeometry((i-1)*pic_scale_x+start_point.x(), (j-1)*pic_scale_y+start_point.y(), pic_scale_x, pic_scale_y);
                map_pic[j][i] -> setScaledContents(true);
                map_pic[j][i] -> show();
            }
            else if (map[j][i]==BRICK)
            {
                int tmp = 1;
                map_pic[j][i] -> setPixmap(QPixmap::fromImage(map_image[tmp]));
                map_pic[j][i] -> setGeometry((i-1)*pic_scale_x+start_point.x(), (j-1)*pic_scale_y+start_point.y(), pic_scale_x, pic_scale_y);
                map_pic[j][i] -> setScaledContents(true);
                map_pic[j][i] -> show();
            }
            else if (map[j][i]==WALL)
            {
                int tmp = 2;
                map_pic[j][i] -> setPixmap(QPixmap::fromImage(map_image[tmp]));
                map_pic[j][i] -> setGeometry((i-1)*pic_scale_x+start_point.x(), (j-1)*pic_scale_y+start_point.y(), pic_scale_x, pic_scale_y);
                map_pic[j][i] -> setScaledContents(true);
                map_pic[j][i] -> show();
            }
            else if (map[j][i]==BOMB)
            {
                int tmp = 3;
                map_pic[j][i] -> setPixmap(QPixmap::fromImage(map_image[tmp]));
                map_pic[j][i] -> setGeometry((i-1)*pic_scale_x+start_point.x(), (j-1)*pic_scale_y+start_point.y(), pic_scale_x, pic_scale_y);
                map_pic[j][i] -> setScaledContents(true);
                map_pic[j][i] -> show();
            }
            else if (map[j][i]==OUT)
            {
                int tmp = 4;
                map_pic[j][i] -> setPixmap(QPixmap::fromImage(map_image[tmp]));
               map_pic[j][i] -> setGeometry((i-1)*pic_scale_x+start_point.x(), (j-1)*pic_scale_y+start_point.y(), pic_scale_x, pic_scale_y);
                map_pic[j][i] -> setScaledContents(true);
                map_pic[j][i] -> show();
            }
            else if (map[j][i]==EXPLODING)
            {
                int tmp = 5;
                map_pic[j][i] -> setPixmap(QPixmap::fromImage(map_image[tmp]));
                map_pic[j][i] -> setGeometry((i-1)*pic_scale_x+start_point.x(), (j-1)*pic_scale_y+start_point.y(), pic_scale_x, pic_scale_y);
                map_pic[j][i] -> setScaledContents(true);
                map_pic[j][i] -> show();
            }
            else
            {

            }
        }
    }

    //explode();
    int j = player->Get_locationy();
    int i = player->Get_locationx();

    QPixmap pix = QPixmap::fromImage(character_image);
    qreal width = pix.width(); //获得以前图片的宽和高
    qreal height = pix.height();
    pix = pix.scaled(width*scale_ratio,height*scale_ratio,Qt::KeepAspectRatio);
    // 绘制人物

    map_pic[j][i] -> setPixmap(QPixmap::fromImage(character_image));
    map_pic[j][i] -> setGeometry((i-1)*pic_scale_x+start_point.x(), (j-1)*pic_scale_y+start_point.y(), pic_scale_x, pic_scale_y);
    map_pic[j][i] -> setScaledContents(true);
    map_pic[j][i] -> show();

    for (int k = 0;k < client_enemy_num; k++)
    {
        if (enemys[k]->Get_HP()<=0) continue;
        int j = enemys[k]->Get_locationy();
        int i = enemys[k]->Get_locationx();

        QPixmap pix = QPixmap::fromImage(enemy_image);
        qreal width = pix.width(); //获得以前图片的宽和高
        qreal height = pix.height();
        pix = pix.scaled(width*scale_ratio,height*scale_ratio,Qt::KeepAspectRatio);

        map_pic[j][i] -> setPixmap(QPixmap::fromImage(enemy_image));
        map_pic[j][i] -> setGeometry((i-1)*pic_scale_x+start_point.x(), (j-1)*pic_scale_y+start_point.y(), pic_scale_x, pic_scale_y);
        map_pic[j][i] -> setScaledContents(true);
        map_pic[j][i] -> show();
    }
//    if (map[j][i] == OUT)
//    {
//        GameStatus = PASS;
//        this->GamePass();
//    }
//    qDebug() << player->Get_locationx() << ' ' << player->Get_locationy() << '\n';
    // TODO
}


void GameDisplay::MapLoad(int idx)
{
    QFile file(map_file_path[idx]);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }
    file.seek(0);
    QTextStream mapdata(&file);
    int i=0;
    while (!mapdata.atEnd()){
        QString line = mapdata.readLine();
        QStringList strlist = line.split(" ");
        for (int j=0;j<20;j++){
            map[i][j] = strlist[j].toInt();
        }
        i++;
    }

}

void GameDisplay::MapUpdate(int** newMap)
{
    int k = 0;
    for(int i=0;i<client_map_size_x;i++){
        for(int j=0;j<client_map_size_y;j++){
            map[i][j] = newMap[i][j];
            if(newMap[i][j]==ISCHARACTER){
                map[i][j]=0;
                player->Set_locationx(i);
                player->Set_locationy(j);
            }
            else if(newMap[i][j]==ISNPC)
            {
                map[i][j]=0;
                enemys[k]->Set_locationx(i);
                enemys[k]->Set_locationy(j);
                k++;
            }
            else if(newMap[i][j]==NPCDEAD)
            {
                map[i][j]=0;
                enemys[k]->Set_locationx(i);
                enemys[k]->Set_locationy(j);
                enemys[k]->Set_HP(0);
                k++;
            }
        }
    }
}
//void GameDisplay::LocationUpdate(QString s)
//{
//    player->Set_locationx(s.at(0).unicode()-'0');
//    player->Set_locationy(s.at(1).unicode()-'0');
//     for (int k = 0;k < client_enemy_num; k++)
//     {
//         enemys[k]->Set_locationx(s.at(2+2*k).unicode()-'0');
//         enemys[k]->Set_locationy(s.at(3+2*k).unicode()-'0');
//     }

//}
