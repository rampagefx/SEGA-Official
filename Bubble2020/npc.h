#ifndef NPC_H
#define NPC_H

#include "character.h"

class npc:public Character{
public:
    npc(int, int, int, int, int);
    void automove(int ** map);
    void skill(SingleGame *);
};

#endif // NPC_H
