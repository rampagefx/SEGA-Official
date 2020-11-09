#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include "singlegame.h"
#include "pikachu.h"

SingleGame::SingleGame(QWidget *parent) : QWidget(parent)
{
    frame = 0;
    this -> resize(windows_size_x, windows_size_y);
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
    map[player->Get_locationy()][player->Get_locationx()] = player->Get_id();
    // Test img read
    map_image[0].load("/Users/admin/Desktop/SE/SEGA-Official/files/black.png");
    map_image[1].load("/Users/admin/Desktop/SE/SEGA-Official/files/white.png");
    character_image.load("/Users/admin/Desktop/SE/SEGA-Official/files/character.png");
    for (int i = 0; i < map_size_x; i++)
    {
        for (int j = 0; j < map_size_y; j++)
        {
            map_pic[j][i] = new QLabel(this);
            if (map[j][i] == 0)
            {
                int tmp = (i+j)%2;
                map_pic[j][i] -> setPixmap(QPixmap::fromImage(map_image[tmp]));
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
    // Test img end
    this -> grabKeyboard();
    QKeyEvent *ev;
    keyPressEvent(ev);
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
    connect(timer,SIGNAL(timeout()), this, SLOT(frame_plus()));
    timer->start(50);

}

void SingleGame::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    for (int i = 0; i < map_size_x; i++)
    {
        for (int j = 0; j < map_size_y; j++)
        {
            if (map[j][i] == 0)
            {
                int tmp = (i+j)%2;
                map_pic[j][i] -> setPixmap(QPixmap::fromImage(map_image[tmp]));
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
    qDebug() << player->Get_locationx() << ' ' << player->Get_locationy() << '\n';
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
}
bool SingleGame::PlaceBomb(int p, int x, int y)
{
    // TODO
    return true;
}
void SingleGame::frame_plus()
{
    frame++;
    return;
}

bool SingleGame::isValid(int x, int y)
{
    if (x<map_size_x && x>-1 && y<map_size_y && y>-1)
        return true;
    else
        return false;
}

int SingleGame::hurtCharacter(int x, int y)
{
    //TODO
    return 1;
}
