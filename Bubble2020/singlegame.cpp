#include "singlegame.h"
#include <QPainter>

const int windows_size = 800;
const int map_size = 20;
SingleGame::SingleGame(QWidget *parent) : QWidget(parent)
{
    frame = 0;
    this -> resize(windows_size, windows_size);
    map = new int*[map_size];
    for (int i = 0; i < map_size; ++i)
    {
        map[i] = new int[map_size];
    }
    for (int i=0; i < map_size; ++i)
        for (int j = 0; j < map_size; ++j)
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
}

void SingleGame::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_W)
    {

    }
}
void SingleGame::frame_plus()
{
    frame++;
    return;
}
