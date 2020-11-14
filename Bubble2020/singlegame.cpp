#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <cstdio>
#include "singlegame.h"
#include "pikachu.h"

SingleGame::SingleGame(QWidget *parent) : QWidget(parent)
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

    // Test character
    player = new Pikachu(1, 101, Player, 10, 10);
    map[15][15] = BRICK;
    map[19][19] = OUT;
    // Test img read
    map_image[0].load("../../../../img/white.png");
    map_image[1].load("../../../../img/bomb.png");
    character_image.load("../../../../img/character.png");
    bomb_image.load("../../../../img/black.png");
    for (int i = 0; i < map_size_x; i++)
    {
        for (int j = 0; j < map_size_y; j++)
        {
            map_pic[j][i] = new QLabel(this);
            map_pic[j][i] -> setPixmap(QPixmap::fromImage(map_image[0]));
            map_pic[j][i] -> setGeometry((i-1)*pic_size_x+start_point.x(), (j-1)*pic_size_y+start_point.y(), pic_size_x, pic_size_y);
            map_pic[j][i] -> setScaledContents(true);
            map_pic[j][i] -> show();
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
            else if (map[j][i]==BOMB)
            {
                map_pic[j][i] -> setPixmap(QPixmap::fromImage(bomb_image));
                map_pic[j][i] -> setGeometry((i-1)*pic_size_x+start_point.x(), (j-1)*pic_size_y+start_point.y(), pic_size_x, pic_size_y);
                map_pic[j][i] -> setScaledContents(true);
                map_pic[j][i] -> show();
            }
            else {
                map_pic[j][i] -> setPixmap(QPixmap::fromImage(character_image));
                map_pic[j][i] -> setGeometry((i-1)*pic_size_x+start_point.x(), (j-1)*pic_size_y+start_point.y(), pic_size_x, pic_size_y);
                map_pic[j][i] -> setScaledContents(true);
                map_pic[j][i] -> show();
            }
        }
    }
    //explode();
    int j = player->Get_locationy();
    int i = player->Get_locationx();
    map_pic[j][i] -> setPixmap(QPixmap::fromImage(character_image));
    map_pic[j][i] -> setGeometry((i-1)*pic_size_x+start_point.x(), (j-1)*pic_size_y+start_point.y(), pic_size_x, pic_size_y);
    map_pic[j][i] -> setScaledContents(true);
    map_pic[j][i] -> show();
    if (map[j][i] == OUT)
            qDebug() << "end";
//    qDebug() << player->Get_locationx() << ' ' << player->Get_locationy() << '\n';
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
    qDebug() << "Add Bomb" << new_bomb->explodeTime << '\n' << bomb_queue.len;
    return true;
}
void SingleGame::frame_plus()
{
    frame++;
//    qDebug() << frame;
    //std::printf("%d\n", frame);
    while (bomb_queue.GetHeadTime()<=frame)
        explode();
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
    //TODO
    qDebug() << "Explosion";
     while (bomb_queue.GetHeadTime()<=frame){
        bomb* theBomb = bomb_queue.pop()->thebomb;
        int dx[4] = {-1,0,1,0};
        int dy[4] = {0,-1,0,1};
        for (int i=0;i<4;i++){
            if (isValid(dx[i]+theBomb->GetX(),dy[i]+theBomb->GetY())){
                int x = dx[i]+theBomb->GetX();
                int y = dy[i]+theBomb->GetY();
                if (map[y][x] == BRICK)
                    map[y][x] = EMPTY;
                if (player->Get_locationx()==x && player->Get_locationy()==y){
                    player->Set_HP(player->Get_HP()-1);
                }

            }
        }
        map[theBomb->GetY()][theBomb->GetX()] = EMPTY;

    }
    return 1;
}

void SingleGame::MapLoad()
{

}
