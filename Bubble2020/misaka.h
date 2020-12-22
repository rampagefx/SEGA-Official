#ifndef MISAKA_H
#define MISAKA_H

#include "character.h"
// 派生出来的misaka人物
class Misaka:public Character
{
public:
    Misaka(int, int ,int, int ,int);
    void skill(int **);
};

#endif // MISAKA_H
