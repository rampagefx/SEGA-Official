#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <cstdlib>
#include <ctime>
#include "doublegame.h"
#include "pikachu.h"
#include "npc.h"

using namespace std;
#define PLAYING 0
#define DEAD 1
#define PASS 2

DoubleGame::DoubleGame(int player_id[], QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    frame = 0;
    GameStatus = 0;
    resize(windows_size_x, windows_size_y);
    map = new int*[map_size_y];
    // Test map
    for (int i = 0; i < map_size_x; ++i)
    {
        map[i] = new int[map_size_x];
    }
    for (int i=0; i < map_size_y; ++i)
        for (int j = 0; j < map_size_x; ++j)
            map[i][j] = 0; // initialize

    // Test map end

    MapLoad();
    switch(player_id[0])
    {
    case 0: player[0] = new Pikachu(1, 1, 1, 2, 10);
    //default: this->close();
    }
    map[10][2] = 100;
    switch(player_id[1])
    {
    case 0: player[1] = new Pikachu(1, 2, 1, 9, 10);
    //default: this->close();
    }
    map[10][2] = 100;
    map[10][9] = 100;
    //Test img read
    map_image[0].load("../img/white.png");
    map_image[1].load("../img/black.png");
    //To be modified if new characters added...
    character_image[0].load("../img/character.png");
    character_image[1].load("../img/character.png");
    enemy_image.load("../img/npc.png");
    bomb_image.load("../img/bomb.png");
    int count = 0; //counter for enemies
    //map_pic initialization
    for (int i = 0; i < map_size_x; i++)
    {
        for (int j = 0; j < map_size_y; j++)
        {
            map_pic[j][i] = new QLabel(this);
            map_pic[j][i] -> setPixmap(QPixmap::fromImage(map_image[0]));
            map_pic[j][i] -> setGeometry((i-1)*pic_size_x+start_point.x(), (j-1)*pic_size_y+start_point.y(), pic_size_x, pic_size_y);
            map_pic[j][i] -> setScaledContents(true);
            map_pic[j][i] -> show();
            if (map[j][i] == 9 && count < enemy_num)
            {
                enemys[count] = new npc(1, count, NPC, i, j);
                map[j][i] = 0;
                count++;
            }
        }
    }
    // Test img end
    grabKeyboard();
    QKeyEvent *ev;
    keyPressEvent(ev);
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
    connect(timer,SIGNAL(timeout()), this, SLOT(frame_plus()));
    timer->start(1);
    setAttribute(Qt::WA_DeleteOnClose);
}

void DoubleGame::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    for (int i = 0; i < map_size_x; i++)
    {
        for (int j = 0; j < map_size_y; j++)
        {//map->map_pic
            if (map[j][i] == 0) //Empty
            {
                int tmp = 0;
                map_pic[j][i] -> setPixmap(QPixmap::fromImage(map_image[tmp]));
                map_pic[j][i] -> setGeometry((i-1)*pic_size_x+start_point.x(), (j-1)*pic_size_y+start_point.y(), pic_size_x, pic_size_y);
                map_pic[j][i] -> setScaledContents(true);
                map_pic[j][i] -> show();
            }
            else if (map[j][i]==BRICK)
            {
                int tmp = 1;
                map_pic[j][i] -> setPixmap(QPixmap::fromImage(map_image[tmp]));
                map_pic[j][i] -> setGeometry((i-1)*pic_size_x+start_point.x(), (j-1)*pic_size_y+start_point.y(), pic_size_x, pic_size_y);
                map_pic[j][i] -> setScaledContents(true);
                map_pic[j][i] -> show();
            }
            else if (map[j][i]==BOMB)
            {
                map_pic[j][i] -> setPixmap(QPixmap::fromImage(bomb_image));
                map_pic[j][i] -> setGeometry((i-1)*pic_size_x+start_point.x(), (j-1)*pic_size_y+start_point.y(), pic_size_x, pic_size_y);
                map_pic[j][i] -> setScaledContents(true);
                map_pic[j][i] -> show();
            }
            else
            {

            }
        }
    }
    //show charater
    for (int i = 0; i<2; i++)
    {
        int x = player[i]->Get_locationx();
        int y = player[i]->Get_locationy();
        map_pic[y][x] -> setPixmap(QPixmap::fromImage(character_image[i]));
        map_pic[y][x] -> setGeometry((x-1)*pic_size_x+start_point.x(), (y-1)*pic_size_y+start_point.y(), pic_size_x, pic_size_y);
        map_pic[y][x] -> setScaledContents(true);
        map_pic[y][x] -> show();
    }
    //show enemy
    for (int k = 0;k < enemy_num; k++)
    {
        if (enemys[k]->Get_HP()<=0) continue;
        int y = enemys[k]->Get_locationy();
        int x = enemys[k]->Get_locationx();
        map_pic[y][x] -> setPixmap(QPixmap::fromImage(enemy_image));
        map_pic[y][x] -> setGeometry((x-1)*pic_size_x+start_point.x(), (y-1)*pic_size_y+start_point.y(), pic_size_x, pic_size_y);
        map_pic[y][x] -> setScaledContents(true);
        map_pic[y][x] -> show();
    }
    //GameStatus determination
    for (int i = 0; i<2; i++)
    {
        int x = player[i]->Get_locationx();
        int y = player[i]->Get_locationy();
        if (map[y][x] == OUT)
        {
            GameStatus = PASS;
            this->GamePass(i);
        }
    }
}

void DoubleGame::keyPressEvent(QKeyEvent *event)
{
    //for player 1
    if(event->key()==Qt::Key_W)
    {
        player[0]->Move(0, map, map_size_x, map_size_y);
    }
    else if(event->key()==Qt::Key_A)
    {
        player[0]->Move(2, map, map_size_x, map_size_y);
    }
    else if(event->key()==Qt::Key_D)
    {
        player[0]->Move(3, map, map_size_x, map_size_y);
    }
    else if(event->key()==Qt::Key_S)
    {
        player[0]->Move(1, map, map_size_x, map_size_y);
    }
    else if (event->key()==Qt::Key_Space)
    {
        PlaceBomb(0, player[0]->Get_locationx(), player[0]->Get_locationy());
    }
    else if (event->key()==Qt::Key_Q)
    {
        player[0]->skill();
    }
    //for player 2
    if(event->key()==Qt::Key_I)
    {
        player[1]->Move(0, map, map_size_x, map_size_y);
    }
    else if(event->key()==Qt::Key_J)
    {
        player[1]->Move(2, map, map_size_x, map_size_y);
    }
    else if(event->key()==Qt::Key_L)
    {
        player[1]->Move(3, map, map_size_x, map_size_y);
    }
    else if(event->key()==Qt::Key_K)
    {
        player[1]->Move(1, map, map_size_x, map_size_y);
    }
    else if (event->key()==Qt::Key_P)
    {
        PlaceBomb(0, player[1]->Get_locationx(), player[1]->Get_locationy());
    }
    else if (event->key()==Qt::Key_U)
    {
        player[1]->skill();
    }
}
bool DoubleGame::PlaceBomb(int p, int x, int y) //放置炸弹
{
    if (map[y][x] == BOMB)
    {
        return false;
    }
    bombStruct *new_bomb = new bombStruct;
    new_bomb->thebomb = new bomb;
    new_bomb->explodeTime = new_bomb->thebomb->Set(p, x, y, map) + frame;
    new_bomb->next = nullptr;
    bomb_queue.push(new_bomb);
    //qDebug() << "Add Bomb" << new_bomb->explodeTime << '\n' << bomb_queue.len;
    return true;
}
void DoubleGame::frame_plus()
{
    frame++;
//    qDebug() << frame;
    //std::printf("%d\n", frame);
    while (bomb_queue.GetHeadTime()<=frame)
        explode();
    if (frame % 2 == 0)
        for (int i=0;i<5;i++)
            if (enemys[i]->Get_HP()>0){
                enemys[i]->automove(map);
            }
    if (frame % 10 == 0)
        for (int i=0;i<5;i++)
            if (enemys[i]->Get_HP()>0){
                // enemys[i]->automove(map);
                qsrand(time(0)+i);
                if (qrand() % 100 > 90)
                    PlaceBomb(0, enemys[i]->Get_locationx(), enemys[i]->Get_locationy());
            }
    return;
}
bool DoubleGame::isValid(int x, int y)
{
    if (x<map_size_x && x>-1 && y<map_size_y && y>-1)
        return true;
    else
        return false;
}

int DoubleGame::explode()
{
    while (bomb_queue.GetHeadTime()<=frame)
    {
        bomb* theBomb = bomb_queue.pop()->thebomb;
        int dx[4] = {-1,0,1,0};
        int dy[4] = {0,-1,0,1};
        for (int i = 0; i < 4; i++)
        {
            if(isValid(dx[i]+theBomb->GetX(),dy[i]+theBomb->GetY()))
            {
                int x = dx[i]+theBomb->GetX();
                int y = dy[i]+theBomb->GetY();
                if (map[y][x] == BRICK)
                    map[y][x] = EMPTY;
                for (int j = 0; j < 2; j++)
                {
                    if (player[j]->Get_locationx()==x && player[j]->Get_locationy()==y)
                    {
                        player[j]->Set_HP(player[0]->Get_HP()-1);
                        if (player[j]->Get_HP() <= 0)
                        {
                            GameOver(j);
                            break;
                        }
                    }
                }
                for (int j  =0; j < 5; j++){
                    if (enemys[j]->Get_locationx()==x && enemys[j]->Get_locationy()==y){
                        enemys[j]->Set_HP(enemys[j]->Get_HP()-1);
                        if (enemys[j]->Get_HP() <= 0)
                            map[y][x] = 0;
                    }
                }
            }
        }
        map[theBomb->GetY()][theBomb->GetX()] = EMPTY;
    }
    return 1;
}

void DoubleGame::MapLoad()
{
    QFile file("../map.txt");
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









