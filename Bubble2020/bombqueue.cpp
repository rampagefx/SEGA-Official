#include "bombqueue.h"

BombQueue::BombQueue() // 构造函数，初始化一个空队列
{
    head = nullptr;
    len = 0;
}

bool BombQueue::push(bombStruct *in)
{
    if (len == 0) // 队列长度为0的时候，直接加入队列中
    {
        // empty queue
        head = in;
        len = 1;
    }
    else if (len == 1) // 队列长度为1的时候，特殊处理
    {
        if (in -> explodeTime <= head -> explodeTime) // 新入队的炸弹爆炸时间较早，变为新的头指针
        {
            in -> next = head;
            head = in;
            len = 2;
        }
        else // 爆炸时间较晚，放在后面
        {
            head -> next = in;
            len = 2;
        }

    }
    else if (in -> explodeTime <= head -> explodeTime) // 新入队的炸弹爆炸时间较早，变为新的头指针
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

bombStruct* BombQueue::pop() // 直接返回头指针，然后出队，长度减1
{
    if (len == 0)
        return nullptr;
    bombStruct *temp = head;
    head = head -> next;
    len--;
    return temp;
}

int BombQueue::GetHeadTime() // 返回当前头指针对应的炸弹的爆炸时间
{
    if (len == 0)
        return 3e8;
    return head -> explodeTime;
}

bombStruct* BombQueue::Gethead(){
    return head;
}
