#ifndef BOMBQUEUE_H
#define BOMBQUEUE_H

#include "bomb.h"
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
