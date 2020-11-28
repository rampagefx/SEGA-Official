#ifndef PIKACHU_H
#define PIKACHU_H

#include "character.h"
// 派生出来的Pikachu人物
class Pikachu:public Character
{
public:
    Pikachu(int, int ,int, int ,int);
    void skill();
};

#endif // PIKACHU_H
