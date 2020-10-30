#ifndef CHARACTER_H
#define CHARACTER_H

#define Player 1
#define NPC 2

#define moving 1
#define non_moving 0

class Character
{
private:
    int HP; // Health Point
    int id; // Character Identity
    int role; // Character Role: Player or NPC
    int location_x, location_y; // location in map
    int status; // moving status
    int status_counter; // remaining frames before character can move again
public:
    Character(int, int ,int, int ,int);
    virtual ~Character();
    int Get_HP();
    int Get_id();
    int Get_role();
    int Get_locationx();
    int Get_locationy();
    void Set_HP(int);
    void Set_id(int);
    void Set_role(int);
    void Set_locationx(int);
    void Set_locationy(int);
    virtual void Skill() = 0;
    void Move(int, int**, int, int);
    void Place_Bomb(int**);
};


#endif // CHARACTER_H
