#ifndef BOMBQUEUE_H
#define BOMBQUEUE_H

#include "bomb.h"
// 炸弹队列，存储游戏中放置的炸弹，这是一个优先队列，队列头部是最近要爆炸的炸弹
class BombQueue
{
private:
    bombStruct *head;
public:
    int len;
    BombQueue();
    bool push(bombStruct*);
    bombStruct* pop();
    int GetHeadTime();
    bombStruct* Gethead();
};

#endif // BOMBQUEUE_H
