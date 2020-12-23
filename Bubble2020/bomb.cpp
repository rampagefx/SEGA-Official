#include "singlegame.h"

bomb::bomb(){

}

int bomb::GetY(){
    return location_y;
}

int bomb::GetX(){
    return location_x;
}
int bomb::GetDamage(){
    return damage;
}

int bomb::Set(int p, int x, int y, int **map){
   property = p;
   location_x = x;
   location_y = y;
   map[y][x] = BOMB;
   switch (property) {        //根据属性设置
   case 0:                    //普通炸弹
       waitingTime = 50;
       damage = 1;
       break;
   case 1:                    // 时间更长的炸弹
       waitingTime = 100;
       damage = 2;
       break;
   default:
       break;
   }
   return waitingTime;
}

