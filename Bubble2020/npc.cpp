#include "npc.h"
#include <ctime>
#include <QDebug>
using namespace std;

npc::npc(int HP_in, int id_in, int role_in, int location_x_in, int location_y_in):
    Character (HP_in, id_in, role_in, location_x_in, location_y_in)
{

}

void npc::automove(int** map){
    qsrand(time(NULL)+this->Get_id());
    int direction = int(qrand()) % 4;
    Move(direction, map, 20, 20);
    //qDebug() << map[Get_locationy()][Get_locationx()-1] << map[Get_locationy()-1][Get_locationx()] << map[Get_locationy()+1][Get_locationx()] << map[Get_locationy()][Get_locationx()+1];
}

void npc::skill(){

}

