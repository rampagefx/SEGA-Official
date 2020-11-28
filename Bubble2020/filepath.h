#ifndef FILEPATH_H
#define FILEPATH_H
// 存储一些常量的头文件
#ifdef __APPLE__
const char *win_pic_path = "../../../../img/win.png";
const char *lose_pic_path = "../../../../img/lose.png";
const char *map_file_path[2] = {"../../../../map1.txt", "../../../../map2.txt"};
const char *map_image_path[5] = {"../../../../img/floor.png",
                                 "../../../../img/brick.png",
                                 "../../../../img/wall.png",
                                 "../../../../img/bomb.png",
                                 "../../../../img/out.png"};
const char *npc_pic_path = "../../../../img/npc.png";
#elif _WIN64
const char *win_pic_path = "";
#endif
#endif // FILEPATH_H
