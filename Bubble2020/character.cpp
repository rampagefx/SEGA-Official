#include "character.h"
bool moveable(int **map, int x, int y, int length, int width) // map[x][y] is moveable or not
{
    bool is_moveable = true;
    if (y >= length || x >= width || x < 0 || y < 0)
        return false;
    switch (map[y][x])
    {
    case 1:is_moveable = false;break;
    case 2:is_moveable = false;break;
    }
    return is_moveable;
}
void map_swap(int **map, int x1, int y1, int x2, int y2) // Swap two points in the map
{
    int temp = map[y1][x1];
    map[y1][x1] = map[y2][x2];
    map[y2][x2] = temp;
}
Character::Character(int HP_in, int id_in, int role_in, int location_x_in, int location_y_in):
    HP(HP_in), id(id_in), role(role_in), location_x(location_x_in), location_y(location_y_in)
{
    status = non_moving;
    status_counter = 0;
}

Character::~Character()
{

}

int Character::Get_HP()
{
    return HP;
}

int Character::Get_id()
{
    return id;
}

int Character::Get_role()
{
    return role;
}

int Character::Get_locationx()
{
    return location_x;
}

int Character::Get_locationy()
{
    return location_y;
}

void Character::Set_HP(int hp_in)
{
    HP = hp_in;
}

void Character::Set_id(int id_in)
{
    id = id_in;
}

void Character::Set_role(int role_in)
{
    role = role_in;
}

void Character::Set_locationx(int location)
{
    location_x = location;
}

void Character::Set_locationy(int location)
{
    location_y = location;
}

void Character::Move(int direction, int **map, int length, int width)
{
    // 0 for up, 1 for down, 2 for left, 3 for right
    int current_x = location_x;
    int current_y = location_y;
    if (0==direction)
    {
        if(moveable(map, current_x, current_y-1, length, width))
        {
            //map_swap(map, current_x, current_y, current_x, current_y-1);
            location_y--;
        }
    }
    else if (1==direction)
    {
        if(moveable(map, current_x, current_y+1, length, width))
        {
            //map_swap(map, current_x, current_y, current_x, current_y+1);
            location_y++;
        }
    }
    else if (2==direction)
    {
        if(moveable(map, current_x-1, current_y, length, width))
        {
            //map_swap(map, current_x, current_y, current_x-1, current_y);
            location_x--;
        }
    }
    else if (3==direction)
    {
        if(moveable(map, current_x+1, current_y, length, width))
        {
            //map_swap(map, current_x, current_y, current_x+1, current_y);
            location_x++;
        }
    }
    else
    {
        throw "Wrong Direction input for character moving!";
    }
}
