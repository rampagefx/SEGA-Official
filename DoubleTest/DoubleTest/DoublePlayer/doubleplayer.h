#ifndef DOUBLEPLAYER_H
#define DOUBLEPLAYER_H

struct Player{
    int xposition;
    int yposition;
    int HP;
    bool alive;
};
struct Bomb{
    int xposition;
    int yposition;
};

int explode(Player*p, Bomb b);

#endif // DOUBLEPLAYER_H
