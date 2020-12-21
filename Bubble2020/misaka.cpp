#include "misaka.h"

Misaka::Misaka(int HP_in, int id_in, int role_in, int location_x_in, int location_y_in):
    Character (HP_in * 2, id_in, role_in, location_x_in, location_y_in)
{
#ifdef __APPLE__
    pic_path = "../../../../img/misaka.png";
    big_pic_path = "../../../../img/misaka_big.png";
    discription = "双倍血量";
#elif _WIN64
    pic_path = "../img/misaka.png";
    big_pic_path = "../img/misaka_big.png";
#endif
}

void Misaka::skill()
{
    return;
}
