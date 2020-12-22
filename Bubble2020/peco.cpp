#include "peco.h"

Pecoliimu::Pecoliimu(int HP_in, int id_in, int role_in, int location_x_in, int location_y_in):
    Character (HP_in, id_in, role_in, location_x_in, location_y_in)
{
#ifdef __APPLE__
    pic_path = "../../../../img/pikachu.png";
    big_pic_path = "../../../../img/pikachu_big.png";
    discription = "佩可莉姆的饭团：恢复一点血量";
#elif _WIN64
    pic_path = "../img/pikachu.png";
    big_pic_path = "../img/pikachu_big.png";
    discription = "佩可莉姆的饭团：恢复一点血量";
#endif
}

void Pecoliimu::skill(int **map)
{
    Set_HP(Get_HP()+1);

    return;
}
