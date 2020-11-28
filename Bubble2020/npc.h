#ifndef NPC_H
#define NPC_H

#include "character.h"
// npc，多了个automove功能，只能用作被AI控制的电脑玩家
class npc:public Character{
public:
    npc(int, int, int, int, int);
    void automove(int ** map);
    void skill();
};

#endif // NPC_H
