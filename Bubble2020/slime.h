#ifndef SLIME_H
#define SLIME_H

#include "character.h"
// 派生出来的Slime人物
class Slime:public Character
{
public:
    Slime(int, int ,int, int ,int);
    void skill();
};

#endif // SLIME_H