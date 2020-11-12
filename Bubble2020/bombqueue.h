#ifndef BOMBQUEUE_H
#define BOMBQUEUE_H

#include "bomb.h"
class BombQueue
{
private:
    bombStruct *head;
    int len;
public:
    BombQueue();
    bool push(bombStruct*);
    bombStruct* pop();
    int GetHeadTime();
};

#endif // BOMBQUEUE_H