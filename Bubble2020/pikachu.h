#ifndef PIKACHU_H
#define PIKACHU_H

#include "character.h"

class Pikachu:public Character
{
public:
    Pikachu(int, int ,int, int ,int);
    void skill(SingleGame *);
};

#endif // PIKACHU_H
