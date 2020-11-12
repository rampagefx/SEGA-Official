#ifndef BOMB_H
#define BOMB_H

#define EMPTY    0 //空地
#define BRICK    1 //可破坏障碍
#define WALL     2 //不可破坏障碍
#define BOMB     3 //炸弹
#define OCCUPIED 100 //有人
class SingleGame;
class bomb
{
public:
    bomb();
    int GetX();
    int GetY();
    int Set(int p, int x, int y, int **);
private:
    int waitingTime;            //爆炸时间
    int property;               //种类
    int damage;                 //伤害值
    int location_x, location_y; //位置
};

struct bombStruct{
    bomb *thebomb;       //指向该炸弹的指针
    int explodeTime;    //该炸弹爆炸的时间
    bombStruct *next;
};
#endif // BOMB_H
