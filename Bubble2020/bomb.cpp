#include "bomb.h"
#include "widget.h"

bomb::bomb(){

}

void bomb::Get(){

}

void bomb::Set(int p, int x, int y){
   property = p;
   location_x = x;
   location_y = y;
   switch (property) {        //根据属性设置
   case 0:                    //普通炸弹
       waitingTime = 10;
       damage = 1;
       break;
   default:
       break;
   }
}

void bomb::explode(int **map, Widget *widget){
    switch (damage){
    case 1:
        int dx[4] = {0,1,0,-1};
        int dy[4] = {-1,0,1,0};
        for (int i=0;i<4;i++){
            if (widget->isValid(location_x+dx[i],location_y+dy[i])){
                int x = location_x+dx[i], y = location_y+dy[i];
                if (map[x][y]==BRICK) map[x][y] = EMPTY;
                else if (map[x][y]>=OCCUPIED){
                    widget->hurtCharacter(map[x][y], damage);
                }
            }
        }
        break;

    }
}
