#ifndef CHARACTER_H
#define CHARACTER_H
#include <QString>
#define Player 1
#define NPC 101

#define moving 1
#define non_moving 0
// 人物的基类，所有人物都应该从这个类进行派生
// 所有的人物都应该由该基类指针指向
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
    int bomb_property=0;
    int last_move=0;
    QString pic_path, big_pic_path, discription;
    Character(int, int ,int, int ,int);
    virtual ~Character();
    int CD_time = 200;
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
    void Move(int, int**, int, int);
    virtual void skill(int **) = 0;
};


#endif // CHARACTER_H
