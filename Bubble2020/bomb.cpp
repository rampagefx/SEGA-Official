#include "singlegame.h"

bomb::bomb(){

}

void bomb::Get(){

}

int bomb::Set(int p, int x, int y, int **map){
   property = p;
   location_x = x;
   location_y = y;
   map[y][x] = BOMB;
   switch (property) {        //根据属性设置
   case 0:                    //普通炸弹
       waitingTime = 10;
       damage = 1;
       break;
   case 1:
       waitingTime = 20;
       damage = 1;
       break;
   default:
       break;
   }
   return waitingTime;
}

void bomb::explode(int **map, SingleGame *game){
    switch (damage){
    case 1:
        int dx[4] = {0,1,0,-1};
        int dy[4] = {-1,0,1,0};
        for (int i=0;i<4;i++){
            if (game->isValid(location_x+dx[i],location_y+dy[i])){
                int x = location_x+dx[i], y = location_y+dy[i];
                if (map[y][x]==BRICK) map[y][x] = EMPTY;
                else if (map[y][x]>=OCCUPIED){
                    game->hurtCharacter(map[y][x], damage);
                }
            }
        }
        break;
    }
}
