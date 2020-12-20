#ifndef FILEPATH_H
#define FILEPATH_H
// 存储一些常量的头文件
#ifdef __APPLE__
    static const char *win_pic_path = "../../../../img/win.png"; // 胜利图片
    static const char *lose_pic_path = "../../../../img/lose.png"; // 失败图片
    static const char *map_file_path[2] = {"../../../../map1.txt", "../../../../map2.txt"}; // 地图文件
    static const char *map_image_path[6] = {"../../../../img/floor.png", // 地面素材文件
                                     "../../../../img/brick.png",  // 可破坏障碍物素材文件
                                     "../../../../img/wall.png",  // 不可破坏障碍物素材文件
                                     "../../../../img/bomb.png",  // 炸弹素材文件
                                     "../../../../img/out.png",  // 出口素材文件
                                    "../../../../img/explode.png"};  // 爆炸特效文件
    static const char *npc_pic_path = "../../../../img/npc.png";  // npc素材文件
    static const char *button_pic_path = "../../../../img/continuebutton.png";  // 按键素材文件
    static const char *bgm_path = "../../../../music/menu.wav";  // BGM素材文件
    static const char *background_pic_path = "../../../../img/menu.jpeg";  // 主界面背景素材文件
    static const char *game_background = "../../../../img/background.jpg";  // 单人游戏素材文件
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
