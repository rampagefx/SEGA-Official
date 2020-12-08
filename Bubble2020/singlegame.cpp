#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QPixmap>
#include <QIcon>
#include <QSize>
#include <cstdlib>
#include <ctime>
#include "singlegame.h"
#include "pikachu.h"
#include "npc.h"
#include "filepath.h"

using namespace std;
#define PLAYING 0
#define DEAD 1
#define PASS 2
const int CD = 500;
SingleGame::SingleGame(int player_id, QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    frame = 0;
    GameStatus = 0;
    resize(windows_size_x, windows_size_y);
    map = new int*[map_size_y];
    for (int i = 0; i < map_size_x; ++i)
    {
        map[i] = new int[map_size_x];
    }
    for (int i=0; i < map_size_y; ++i)
        for (int j = 0; j < map_size_x; ++j)
            map[i][j] = 0; // initialize
    MapLoad(0);
    switch (player_id)
    {
    case 0: player = new Pikachu(1, 101, 1, 10, 10);
    //default: this->close();
    }
    // Test img read
    for(int i = 0; i < 6; i++)
        map_image[i].load(map_image_path[i]);
    character_image.load(player->pic_path);
//    bomb_image.load(map_image_path[3]);
    enemy_image.load(npc_pic_path);
    player_image.load(player->big_pic_path);
    player_profile = new QLabel(this);
    player_profile->setPixmap(QPixmap::fromImage(player_image));
    player_profile->setGeometry(750, 50, 200, 200);
    player_profile->show();
    LabelPicturePause=new QLabel(this);
    int count = 0;
    for (int i = 0; i < map_size_x; i++)
    {
        for (int j = 0; j < map_size_y; j++)
        {
            map_pic[j][i] = new QLabel(this);
            map_pic[j][i] -> setPixmap(QPixmap::fromImage(map_image[0]));
            map_pic[j][i] -> setGeometry((i-1)*pic_size_x+start_point.x(), (j-1)*pic_size_y+start_point.y(), pic_size_x, pic_size_y);
            map_pic[j][i] -> setScaledContents(true);
            map_pic[j][i] -> show();
            if (map[j][i] == NPCMAP && count < enemy_num)
            {
                enemys[count] = new npc(1, count, NPC, i, j);
                map[j][i] = 0;
                count++;
            }
        }
    }
    discription[2] = new QLabel(this);
    discription[2]->setGeometry(775, 275, 200, 100);
    discription[2]->setText(player->discription);
    background_image.load(game_background);
    game_back = new QLabel(this);
    game_back->setGeometry(0, 0, 1000, 730);
    game_back->setPixmap(QPixmap::fromImage(background_image));
    game_back->show();
    game_back->lower();
    grabKeyboard();
    QKeyEvent *ev;
    keyPressEvent(ev);
    HP_show = new QLCDNumber(this);
    HP_show->setGeometry(800, 500, 100, 50);
    CD_display = new QProgressBar(this);
    CD_display->setMaximum(CD);
    CD_display->setGeometry(800, 600, 100, 50);
    CD_display->setValue(CD);
    CD_display->show();
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
    connect(timer,SIGNAL(timeout()), this, SLOT(frame_plus()));
    timer->start(1);
    setAttribute(Qt::WA_DeleteOnClose);
}

void SingleGame::paintEvent(QPaintEvent *event)
{
    //qDebug() << "paint";
    QPainter painter;
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
            else if (map[j][i]==OUT)
            {
                int tmp = 4;
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
    //explode();
    // 绘制人物
    int j = player->Get_locationy();
    int i = player->Get_locationx();
    map_pic[j][i] -> setPixmap(QPixmap::fromImage(character_image));
    map_pic[j][i] -> setGeometry((i-1)*pic_size_x+start_point.x(), (j-1)*pic_size_y+start_point.y(), pic_size_x, pic_size_y);
    map_pic[j][i] -> setScaledContents(true);
    map_pic[j][i] -> show();
    for (int k = 0;k < enemy_num; k++)
    {
        if (enemys[k]->Get_HP()<=0) continue;
        int j = enemys[k]->Get_locationy();
        int i = enemys[k]->Get_locationx();
        map_pic[j][i] -> setPixmap(QPixmap::fromImage(enemy_image));
        map_pic[j][i] -> setGeometry((i-1)*pic_size_x+start_point.x(), (j-1)*pic_size_y+start_point.y(), pic_size_x, pic_size_y);
        map_pic[j][i] -> setScaledContents(true);
        map_pic[j][i] -> show();
    }
    if (map[j][i] == OUT)
    {
        GameStatus = PASS;
        timer->stop();
        QImage imaWin;
        imaWin.load(win_pic_path);
        imaWin.scaled(200,100,Qt::KeepAspectRatio);
        LabelPicturePause->setPixmap(QPixmap::fromImage(imaWin));
        LabelPicturePause->setGeometry(150,000,500,342);
        LabelPicturePause->setScaledContents(true);
        LabelPicturePause->raise();
        LabelPicturePause->show();
        QPixmap button_img(button_pic_path);
        next_level = new QPushButton(this);
        next_level->setGeometry(200, 300, 400, 300);
        next_level->setIcon(QIcon(button_img));
        next_level->setIconSize(QSize(400, 300));
        next_level->setStyleSheet("border:none");
        next_level->show();
        connect(next_level, SIGNAL(clicked()), this, SLOT(close()));
    }
    // TODO
}

void SingleGame::keyPressEvent(QKeyEvent *event)
{
    // TODO
    if(event->key()==Qt::Key_W)
    {
        player->Move(0, map, map_size_x, map_size_y);
    }
    else if(event->key()==Qt::Key_A)
    {
        player->Move(2, map, map_size_x, map_size_y);
    }
    else if(event->key()==Qt::Key_D)
    {
        player->Move(3, map, map_size_x, map_size_y);
    }
    else if(event->key()==Qt::Key_S)
    {
        player->Move(1, map, map_size_x, map_size_y);
    }
    else if (event->key()==Qt::Key_Space)
    {
        PlaceBomb(0, player->Get_locationx(), player->Get_locationy());
    }
    else if (event->key()==Qt::Key_Q)
    {
        if (player->CD_time < frame)
        {
            player->skill();
            player->CD_time = frame + CD;
        }
    }
}
bool SingleGame::PlaceBomb(int p, int x, int y)
{
    // p = property
    if (map[y][x] == BOMB)
    {
        // qDebug() << "????????";
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
void SingleGame::frame_plus()
{
    frame++;
//    qDebug() << frame;
    //std::printf("%d\n", frame);
    if (bomb_queue.GetHeadTime()<=frame+10)
    {
        bomb *theBomb = bomb_queue.Gethead()->thebomb;
        int dx[4] = {-1,0,1,0};
        int dy[4] = {0,-1,0,1};
        map[theBomb->GetY()][theBomb->GetX()] = EXPLODING;
        for (int i=0;i<4;i++){
            if (isValid(dx[i]+theBomb->GetX(),dy[i]+theBomb->GetY())){
                int x = dx[i]+theBomb->GetX();
                int y = dy[i]+theBomb->GetY();
                if (map[y][x] == BRICK || map[y][x] == EMPTY)
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
    CD_display->setValue(max(player->CD_time-frame, 0));
    HP_show->display(player->Get_HP());
    return;
}

bool SingleGame::isValid(int x, int y)
{
    if (x<map_size_x && x>-1 && y<map_size_y && y>-1)
        return true;
    else
        return false;
}

int SingleGame::explode()
{
    while (bomb_queue.GetHeadTime()<=frame){
        bomb* theBomb = bomb_queue.pop()->thebomb;
        int dx[4] = {-1,0,1,0};
        int dy[4] = {0,-1,0,1};
        for (int i=0;i<4;i++){
            if (isValid(dx[i]+theBomb->GetX(),dy[i]+theBomb->GetY())){
                int x = dx[i]+theBomb->GetX();
                int y = dy[i]+theBomb->GetY();
                if (map[y][x] == EXPLODING)
                    map[y][x] = EMPTY;
                if (player->Get_locationx()==x && player->Get_locationy()==y){
                    player->Set_HP(player->Get_HP()-1);
                    if (player->Get_HP() <= 0)
                    {
                        GameStatus = DEAD;
                        QImage imaWin;
                        imaWin.load(lose_pic_path);
                        imaWin.scaled(200,100,Qt::KeepAspectRatio);
                        LabelPicturePause->setPixmap(QPixmap::fromImage(imaWin));
                        LabelPicturePause->setGeometry(150,0,500,342);
                        LabelPicturePause->setScaledContents(true);
                        LabelPicturePause->raise();
                        LabelPicturePause->show();

                        timer->stop();
                    }
                }
                for (int j=0;j<5;j++){
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

void SingleGame::MapLoad(int idx)
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

void SingleGame::next_game()
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
