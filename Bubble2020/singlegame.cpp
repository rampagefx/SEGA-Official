#include "singlegame.h"
#include <QPainter>


SingleGame::SingleGame(QWidget *parent) : QWidget(parent)
{
    frame = 0;
    this -> resize(windows_size_x, windows_size_y);
    map = new int*[map_size_y];
    for (int i = 0; i < map_size_x; ++i)
    {
        map[i] = new int[map_size_x];
    }
    for (int i=0; i < map_size_y; ++i)
        for (int j = 0; j < map_size_x; ++j)
            map[i][j] = 0; // initialize
    map[10][10] = 101;
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
    // TODO
}

void SingleGame::keyPressEvent(QKeyEvent *event)
{
    // TODO
    if(event->key()==Qt::Key_W)
    {

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
