#include "pikachu.h"

Pikachu::Pikachu(int HP_in, int id_in, int role_in, int location_x_in, int location_y_in):
    Character (HP_in, id_in, role_in, location_x_in, location_y_in)
{
#ifdef __APPLE__
    pic_path = "../../../../img/pikachu.png";
    big_pic_path = "../../../../img/pikachu_big.png";
    discription = "皮卡丘的高速移动：沿着之前\n移动方向闪现2格";
#elif _WIN64
    pic_path = "../img/pikachu.png";
    big_pic_path = "../img/pikachu_big.png";
    discription = "皮卡丘的高速移动：沿着之前\n移动方向闪现2格";
#endif
}

void Pikachu::skill(int **map)
{
    Move(last_move, map, 20, 20);
    Move(last_move, map, 20, 20);
    return;
}
