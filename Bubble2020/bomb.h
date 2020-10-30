#ifndef BLOCK_H
#define BLOCK_H
#define EMPTY    0 //空地
#define BRICK    1 //可破坏障碍
#define WALL     2 //不可破坏障碍
#define BOMB     3 //炸弹
#define OCCUPIED 4 //有人


#include "widget.h"



class bomb
{
public:
    bomb();
    void Get();
    void Set(int p, int x, int y);
    void explode(int **map, Widget *widget);
private:
    int waitingTime;            //爆炸时间
    int property;               //种类
    int damage;                 //伤害值
    int location_x, location_y; //位置
};

#endif // BOMB_H
