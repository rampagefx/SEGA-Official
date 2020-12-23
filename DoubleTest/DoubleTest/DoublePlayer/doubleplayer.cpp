#include "doubleplayer.h"


int explode(Player* p, Bomb b)
{
    int tst_flag;
    int dx[4] = {-1,0,1,0};
    int dy[4] = {0,-1,0,1};
    for(int i = 0; i < 4; i++){
        int x = dx[i]+b.xposition;
        int y = dy[i]+b.yposition;
        for(int j = 0; j < 2; j++){
            if(p[j].xposition == x && p[j].yposition ==y){
                p[j].HP = p[j].HP - 1;
                if(p[j].HP <= 0)p[j].alive = false;
            }
        }
        if(p[0].alive && p[1].alive)
            tst_flag = 0;
        else if(!(p[0].alive) && p[1].alive)
            tst_flag = 1;
        else if(p[0].alive && !(p[1].alive))
            tst_flag = 2;
        else
            tst_flag = 3;
    }
    return tst_flag;
}
