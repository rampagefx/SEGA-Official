#include "tst_tst.h"
#include "../DoublePlayer/doubleplayer.h"

TEST(DEMO1,CASE1){
    Player* p = new Player[2];
    Bomb b;
    p[0].xposition = 5;
    p[0].yposition = 6;
    p[0].HP = 2;
    p[1].xposition = 7;
    p[1].yposition = 6;
    p[1].HP = 1;
    b.xposition = 2;
    b.yposition = 2;
    EXPECT_EQ(explode(p,b),0);
    delete[] p;
}
TEST(DEMO2,CASE1){
    Player* p = new Player[2];
    Bomb b;
    p[0].xposition = 5;
    p[0].yposition = 6;
    p[0].HP = 2;
    p[1].xposition = 7;
    p[1].yposition = 6;
    p[1].HP = 1;
    b.xposition = 5;
    b.yposition = 5;
    EXPECT_EQ(explode(p,b),0);
    delete[] p;
}
TEST(DEMO2,CASE2){
    Player* p = new Player[2];
    Bomb b;
    p[0].xposition = 5;
    p[0].yposition = 6;
    p[0].HP = 1;
    p[1].xposition = 7;
    p[1].yposition = 6;
    p[1].HP = 1;
    b.xposition = 5;
    b.yposition = 5;
    EXPECT_EQ(explode(p,b),1);
    delete[] p;
}
TEST(DEMO3,CASE1){
    Player* p = new Player[2];
    Bomb b;
    p[0].xposition = 5;
    p[0].yposition = 6;
    p[0].HP = 2;
    p[1].xposition = 7;
    p[1].yposition = 6;
    p[1].HP = 2;
    b.xposition = 7;
    b.yposition = 5;
    EXPECT_EQ(explode(p,b),0);
    delete[] p;
}
TEST(DEMO3,CASE2){
    Player* p = new Player[2];
    Bomb b;
    p[0].xposition = 5;
    p[0].yposition = 6;
    p[0].HP = 2;
    p[1].xposition = 7;
    p[1].yposition = 6;
    p[1].HP = 1;
    b.xposition = 7;
    b.yposition = 5;
    EXPECT_EQ(explode(p,b),2);
    delete[] p;
}
TEST(DEMO4,CASE1){
    Player* p = new Player[2];
    Bomb b;
    p[0].xposition = 5;
    p[0].yposition = 6;
    p[0].HP = 2;
    p[1].xposition = 7;
    p[1].yposition = 6;
    p[1].HP = 2;
    b.xposition = 6;
    b.yposition = 6;
    EXPECT_EQ(explode(p,b),0);
    delete[] p;
}
TEST(DEMO4,CASE2){
    Player* p = new Player[2];
    Bomb b;
    p[0].xposition = 5;
    p[0].yposition = 6;
    p[0].HP = 2;
    p[1].xposition = 7;
    p[1].yposition = 6;
    p[1].HP = 1;
    b.xposition = 6;
    b.yposition = 6;
    EXPECT_EQ(explode(p,b),2);
    delete[] p;
}
TEST(DEMO4,CASE3){
    Player* p = new Player[2];
    Bomb b;
    p[0].xposition = 5;
    p[0].yposition = 6;
    p[0].HP = 1;
    p[1].xposition = 7;
    p[1].yposition = 6;
    p[1].HP = 2;
    b.xposition = 6;
    b.yposition = 6;
    EXPECT_EQ(explode(p,b),1);
    delete[] p;
}
TEST(DEMO4,CASE4){
    Player* p = new Player[2];
    Bomb b;
    p[0].xposition = 5;
    p[0].yposition = 6;
    p[0].HP = 1;
    p[1].xposition = 7;
    p[1].yposition = 6;
    p[1].HP = 1;
    b.xposition = 6;
    b.yposition = 6;
    EXPECT_EQ(explode(p,b),3);
    delete[] p;
}
