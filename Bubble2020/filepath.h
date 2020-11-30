#ifndef FILEPATH_H
#define FILEPATH_H
// 存储一些常量的头文件
#ifdef __APPLE__
const char *win_pic_path = "../../../../img/win.png";
const char *lose_pic_path = "../../../../img/lose.png";
const char *map_file_path[2] = {"../../../../map1.txt", "../../../../map2.txt"};
const char *map_image_path[6] = {"../../../../img/floor.png",
                                 "../../../../img/brick.png",
                                 "../../../../img/wall.png",
                                 "../../../../img/bomb.png",
                                 "../../../../img/out.png",
                                "../../../../img/explode.png"};
const char *npc_pic_path = "../../../../img/npc.png";
const char *button_pic_path = "../../../../img/continuebutton.png";
#elif _WIN64
const char *win_pic_path = "../img/win.png";
const char *lose_pic_path = "../img/lose.png";
const char *map_file_path[2] = {"../map1.txt", "../map2.txt"};
const char *map_image_path[6] = {"../img/floor.png",
                                 "../img/brick.png",
                                 "../img/wall.png",
                                 "../img/bomb.png",
                                 "../img/out.png",
                                "../img/explode.png"};
const char *npc_pic_path = "../img/npc.png";
const char *button_pic_path = "../img/continuebutton.png";
#endif
#endif // FILEPATH_H
