#ifndef FILEPATH_H
#define FILEPATH_H
// 存储一些常量的头文件
#ifdef __APPLE__
    static const char *win_pic_path = "../../../../img/win.png";
    static const char *lose_pic_path = "../../../../img/lose.png";
    static const char *map_file_path[2] = {"../../../../map1.txt", "../../../../map2.txt"};
    static const char *map_image_path[6] = {"../../../../img/floor.png",
                                     "../../../../img/brick.png",
                                     "../../../../img/wall.png",
                                     "../../../../img/bomb.png",
                                     "../../../../img/out.png",
                                    "../../../../img/explode.png"};
    static const char *npc_pic_path = "../../../../img/npc.png";
    static const char *button_pic_path = "../../../../img/continuebutton.png";
    static const char *bgm_path = "../../../../music/menu.wav";
    static const char *background_pic_path = "../../../../img/menu.jpeg";
    const char *game_background = "../../../../img/background.jpg";
#elif _WIN64
    static const char *win_pic_path = "../img/win.png";
    static const char *lose_pic_path = "../img/lose.png";
    static const char *map_file_path[2] = {"../map1.txt", "../map2.txt"};
    static const char *map_image_path[6] = {"../img/floor.png",
                                     "../img/brick.png",
                                     "../img/wall.png",
                                     "../img/bomb.png",
                                     "../img/out.png",
                                    "../img/explode.png"};
    static const char *npc_pic_path = "../img/npc.png";
    static const char *button_pic_path = "../img/continuebutton.png";
    static const char *bgm_path = "../music/menu.wav";
    static const char *background_pic_path = "../img/menu.jpeg";
#endif
#endif // FILEPATH_H
