#include "bombqueue.h"

BombQueue::BombQueue()
{
    head = nullptr;
    len = 0;
}

bool BombQueue::push(bombStruct *in)
{
    if (len == 0)
    {
        // empty queue
        head = in;
        len = 1;
    }
    else if (len == 1)
    {
        if (in -> explodeTime <= head -> explodeTime)
        {
            in -> next = head;
            head = in;
            len = 2;
        }
        else
        {
            head -> next = in;
            len = 2;
        }

    }
    else if (in -> explodeTime <= head -> explodeTime)
    {
        // HEAD needs more time to explode
        in -> next = head;
        head = in;
        len++;
    }
    else
    {
        bombStruct *temp = head;
        while (temp != nullptr)
        {
            if (temp -> next != nullptr && in -> explodeTime > temp -> next ->explodeTime)
                // Next node is not null and needs less time to explode
                temp = temp -> next;
            else
            {
                // Next node is null or needs longer time to explode
//                bombStruct *tmp =
                in -> next = temp -> next;
                temp -> next = in;
                break;
            }
        }
        len++;
    }
    return true;
}

bombStruct* BombQueue::pop()
{
    if (len == 0)
        return nullptr;
    bombStruct *temp = head;
    head = head -> next;
    len--;
    return temp;
}

int BombQueue::GetHeadTime()
{
    if (len == 0)
        return 3e8;
    return head -> explodeTime;
}

bombStruct* BombQueue::Gethead(){
    return head;
}
