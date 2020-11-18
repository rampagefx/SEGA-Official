#ifndef PIKACHU_H
#define PIKACHU_H

#include "character.h"

class Pikachu:public Character
{
public:
    Pikachu(int, int ,int, int ,int);
    void skill();
};

#endif // PIKACHU_H
