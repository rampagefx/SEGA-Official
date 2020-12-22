#ifndef SLIME_H
#define SLIME_H

#include "character.h"
// 派生出来的Pecoliimu人物
class Pecoliimu:public Character
{
public:
    Pecoliimu(int, int ,int, int ,int);
    void skill(int **);
};

#endif // SLIME_H
