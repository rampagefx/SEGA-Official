#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QPixmap>
#include <QIcon>
#include <QSize>
#include <cstdlib>
#include <ctime>
#include "doublegame.h"
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

    MapLoad(0);
    switch(player_id[0])
    {
        case 0: player[0] = new Pikachu(1, 1, 1, 2, 10);break;
        case 1: player[0] = new Misaka(1,1,1,2,10); break;
        case 2: player[0] = new Pecoliimu(1,1,1,2,10); break;
    }
    map[10][2] = 100;
    switch(player_id[1])
    {
        case 0: player[1] = new Pikachu(1, 2, 1, 9, 10); break;
        case 1: player[1] = new Misaka(1,2,1,9,10); break;
        case 2: player[1] = new Pecoliimu(1,2,1,9,10); break;
    }
    map[10][9] = 100;
    //Test img read
    for(int i = 0; i < 6; i++)
        map_image[i].load(map_image_path[i]);
    character_image[0].load(player[0]->pic_path);
    character_image[1].load(player[1]->pic_path);
//    bomb_image.load(map_image_path[3]);
    enemy_image.load(npc_pic_path);
    player_image[0].load(player[0]->big_pic_path);
    player_image[1].load(player[1]->big_pic_path);
    player_profile[0] = new QLabel(this);
    player_profile[0]->setPixmap(QPixmap::fromImage(player_image[0]));
    player_profile[0]->setGeometry(50, 50, 200, 200);
    player_profile[0]->show();
    player_profile[1] = new QLabel(this);
    player_profile[1]->setPixmap(QPixmap::fromImage(player_image[1]));
    player_profile[1]->setGeometry(750+286, 50, 200, 200);
    player_profile[1]->show();
    LabelPicturePause=new QLabel(this);

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
    discription[2] = new QLabel(this);
    discription[2]->setGeometry(775+286, 275, 200, 100);
    discription[2]->setText(player[1]->discription);
    discription[1] = new QLabel(this);
    discription[1]->setGeometry(50, 275, 200, 100);
    discription[1]->setText(player[0]->discription);
    background_image.load(game_background_double);
    game_back = new QLabel(this);
    game_back->setGeometry(0, 0, 1286, 730);
    game_back->setPixmap(QPixmap::fromImage(background_image));
    game_back->show();
    game_back->lower();
    // Test img end
    grabKeyboard();
 //   QKeyEvent *ev;
 //   keyPressEvent(ev);

    HP_show[0] = new QLCDNumber(this);
    HP_show[0]->setGeometry(100, 500, 100, 50);
    CD_display[0] = new QProgressBar(this);
    CD_display[0]->setMaximum(CD);
    CD_display[0]->setGeometry(100, 600, 100, 50);
    CD_display[0]->setValue(CD);
    CD_display[0]->show();
    HP_show[1] = new QLCDNumber(this);
    HP_show[1]->setGeometry(800+286, 500, 100, 50);
    CD_display[1] = new QProgressBar(this);
    CD_display[1]->setMaximum(CD);
    CD_display[1]->setGeometry(800+286, 600, 100, 50);
    CD_display[1]->setValue(CD);
    CD_display[1]->show();

    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
    connect(timer,SIGNAL(timeout()), this, SLOT(frame_plus()));
    timer->start(1);
    setAttribute(Qt::WA_DeleteOnClose);
}

void DoubleGame::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    //show map
    for (int i = 0; i < map_size_x; i++)
    {
        for (int j = 0; j < map_size_y; j++)
        {
            if (map[j][i] == 0)
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
            else if (map[j][i]==WALL)
            {
                int tmp = 2;
                map_pic[j][i] -> setPixmap(QPixmap::fromImage(map_image[tmp]));
                map_pic[j][i] -> setGeometry((i-1)*pic_size_x+start_point.x(), (j-1)*pic_size_y+start_point.y(), pic_size_x, pic_size_y);
                map_pic[j][i] -> setScaledContents(true);
                map_pic[j][i] -> show();
            }
            else if (map[j][i]==BOMB)
            {
                int tmp = 3;
                map_pic[j][i] -> setPixmap(QPixmap::fromImage(map_image[tmp]));
                map_pic[j][i] -> setGeometry((i-1)*pic_size_x+start_point.x(), (j-1)*pic_size_y+start_point.y(), pic_size_x, pic_size_y);
                map_pic[j][i] -> setScaledContents(true);
                map_pic[j][i] -> show();
            }
            else if (map[j][i]==EXPLODING)
            {
                int tmp = 5;
                map_pic[j][i] -> setPixmap(QPixmap::fromImage(map_image[tmp]));
                map_pic[j][i] -> setGeometry((i-1)*pic_size_x+start_point.x(), (j-1)*pic_size_y+start_point.y(), pic_size_x, pic_size_y);
                map_pic[j][i] -> setScaledContents(true);
                map_pic[j][i] -> show();
            }
            else
            {

            }
        }
    }
    // 绘制人物
    for (int i = 0; i<2; i++)
    {
        int x = player[i]->Get_locationx();
        int y = player[i]->Get_locationy();
        map_pic[y][x] -> setPixmap(QPixmap::fromImage(character_image[i]));
        map_pic[y][x] -> setGeometry((x-1)*pic_size_x+start_point.x(), (y-1)*pic_size_y+start_point.y(), pic_size_x, pic_size_y);
        map_pic[y][x] -> setScaledContents(true);
        map_pic[y][x] -> show();
    }
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
        player[0]->last_move = 0;
    }
    else if(event->key()==Qt::Key_A)
    {
        player[0]->Move(2, map, map_size_x, map_size_y);
        player[0]->last_move = 2;
    }
    else if(event->key()==Qt::Key_D)
    {
        player[0]->Move(3, map, map_size_x, map_size_y);
        player[0]->last_move = 3;
    }
    else if(event->key()==Qt::Key_S)
    {
        player[0]->Move(1, map, map_size_x, map_size_y);
        player[0]->last_move = 1;
    }
    else if (event->key()==Qt::Key_Space)
    {
        PlaceBomb(player[0]->bomb_property, player[0]->Get_locationx(), player[0]->Get_locationy());
    }
    else if (event->key()==Qt::Key_Q)
    {
        if(player[0]->CD_time < frame)
        {
              player[0]->skill(map);
              player[0]->CD_time = frame + CD;
        }
    }
    //for player 2
    if(event->key()==Qt::Key_I)
    {
        player[1]->Move(0, map, map_size_x, map_size_y);
        player[1]->last_move = 0;
    }
    else if(event->key()==Qt::Key_J)
    {
        player[1]->Move(2, map, map_size_x, map_size_y);
        player[1]->last_move = 2;
    }
    else if(event->key()==Qt::Key_L)
    {
        player[1]->Move(3, map, map_size_x, map_size_y);
        player[1]->last_move = 3;
    }
    else if(event->key()==Qt::Key_K)
    {
        player[1]->Move(1, map, map_size_x, map_size_y);
        player[1]->last_move = 1;
    }
    else if (event->key()==Qt::Key_P)
    {
        PlaceBomb(player[1]->bomb_property, player[1]->Get_locationx(), player[1]->Get_locationy());
    }
    else if (event->key()==Qt::Key_U)
    {
        if(player[1]->CD_time < frame)
        {
              player[1]->skill(map);
              player[1]->CD_time = frame + CD;
        }
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
    if (bomb_queue.GetHeadTime()<=frame+10)
    {
        bomb *theBomb = bomb_queue.Gethead()->thebomb;
        int dx[5] = {-1,0,1,0,0};
        int dy[5] = {0,-1,0,1,0};
        map[theBomb->GetY()][theBomb->GetX()] = EXPLODING;
        for (int i=0;i<5;i++){
            if (isValid(dx[i]+theBomb->GetX(),dy[i]+theBomb->GetY())){
                int x = dx[i]+theBomb->GetX();
                int y = dy[i]+theBomb->GetY();
                if (map[y][x] == BRICK || map[y][x] == EMPTY)
                    map[y][x] = EXPLODING;
                if (map[y][x] == WALL && theBomb->GetDamage() == 2)
                    map[y][x] = EXPLODING;
            }
        }
    }
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
    CD_display[0]->setValue(max(player[0]->CD_time-frame, 0));
    HP_show[0]->display(player[0]->Get_HP());
    CD_display[1]->setValue(max(player[1]->CD_time-frame, 0));
    HP_show[1]->display(player[1]->Get_HP());
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
        int dx[5] = {-1,0,1,0,0};
        int dy[5] = {0,-1,0,1,0};
        for (int i = 0; i < 5; i++)
        {
            if(isValid(dx[i]+theBomb->GetX(),dy[i]+theBomb->GetY()))
            {
                int x = dx[i]+theBomb->GetX();
                int y = dy[i]+theBomb->GetY();
                if (map[y][x] == EXPLODING)
                    map[y][x] = EMPTY;
                for (int j = 0; j < 2; j++)
                {
                    if (player[j]->Get_locationx()==x && player[j]->Get_locationy()==y)
                    {
                        player[j]->Set_HP(player[j]->Get_HP()-theBomb->GetDamage());
                    }
                }
                for (int j  =0; j < 5; j++){
                    if (enemys[j]->Get_locationx()==x && enemys[j]->Get_locationy()==y){
                        enemys[j]->Set_HP(enemys[j]->Get_HP()-theBomb->GetDamage());
                        if (enemys[j]->Get_HP() <= 0)
                            map[y][x] = 0;
                    }
                }
            }
        }
        map[theBomb->GetY()][theBomb->GetX()] = EMPTY;
    }

    if (player[0]->Get_HP() <= 0 && player[1]->Get_HP() <= 0)       // 平局
    {
        GameStatus = DEAD;
        QImage imaWin;
        imaWin.load(draw_pic_path_double);
        imaWin.scaled(200,100,Qt::KeepAspectRatio);
        LabelPicturePause->setPixmap(QPixmap::fromImage(imaWin));
        LabelPicturePause->setGeometry(150+286,0,500,342);
        LabelPicturePause->setScaledContents(true);
        LabelPicturePause->raise();
        LabelPicturePause->show();
        timer->stop();
    }
    else if(player[0]->Get_HP() <= 0)
    {
        GameStatus = DEAD;
        QImage imaWin;
        imaWin.load(win_pic_path_double_2);
        imaWin.scaled(200,100,Qt::KeepAspectRatio);
        LabelPicturePause->setPixmap(QPixmap::fromImage(imaWin));
        LabelPicturePause->setGeometry(150+286,0,500,342);
        LabelPicturePause->setScaledContents(true);
        LabelPicturePause->raise();
        LabelPicturePause->show();
        timer->stop();
    }
    else if(player[1]->Get_HP() <= 0)
    {
        GameStatus = DEAD;
        QImage imaWin;
        imaWin.load(win_pic_path_double_1);
        imaWin.scaled(200,100,Qt::KeepAspectRatio);
        LabelPicturePause->setPixmap(QPixmap::fromImage(imaWin));
        LabelPicturePause->setGeometry(150+286,0,500,342);
        LabelPicturePause->setScaledContents(true);
        LabelPicturePause->raise();
        LabelPicturePause->show();
        timer->stop();
    }
    return 1;
}

void DoubleGame::MapLoad(int idx)
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

void DoubleGame::next_game()
{
    MapLoad(1);
    frame = 0;
    LabelPicturePause->close();
    next_level->setVisible(false);
    next_level->close();
    delete next_level;
    repaint();
    timer->start(1);
}
