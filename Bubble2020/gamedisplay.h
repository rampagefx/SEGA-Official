#ifndef GAMEDISPLAY_H
#define GAMEDISPLAY_H
#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QLabel>
#include <QImage>
#include <QPoint>
#include <QLCDNumber>
#include <QProgressBar>
#include <QPushButton>
#include <QString>
#include "character.h"
#include "bomb.h"
#include "bombqueue.h"
#include "npc.h"

#define PLAYING 0
#define DEAD 1
#define PASS 2
#define ISCHARACTER 6
#define ISNPC 7
#define NPCDEAD 8

const int client_size_x = 1500; // 窗口尺寸
const int client_size_y = 730;
const int client_map_size_x = 20; // 地图尺寸（格子数量）
const int client_map_size_y = 20;
const int client_pic_size_x = 35; // 图片尺寸（像素）
const int client_pic_size_y = 35;
const int client_enemy_num = 5; // AI的数量
const float scale_ratio = 0.4;

//旁边的小窗口展示的类
class GameDisplay: public QWidget
{
    Q_OBJECT
public:
    QTimer *timer;
    int frame;
    int** map;
    int GameStatus;
    Character *player;
    npc *enemys[client_enemy_num];
    QLabel *map_pic[client_map_size_y][client_map_size_x];
    QLabel *LabelPicturePause;
    QLabel *character_pic, *character_name;
    QLabel *player_profile;
    QLabel *discription[3];
    QLabel *game_back;
    QImage map_image[6];
    QImage character_image;
    QImage enemy_image;
    QImage player_image;
    QImage background_image;
//    QImage bomb_image;
    QPushButton *next_level;
    QPoint start_point = QPoint(1050, 50); //窗口位置
    QLCDNumber *HP_show;
    QProgressBar *CD_display;
    BombQueue bomb_queue;


    explicit GameDisplay(int, QWidget *parent = nullptr);
    // TODO
    bool PlaceBomb(int p, int x, int y);
    bool isValid(int x, int y); // out of map or not
    void MapUpdate(int** newMap);
//    void LocationUpdate(QString s);
    int explode();
signals:
    void GameOver();
    void GamePass();
protected:
    void paintEvent(QPaintEvent *event);
    void MapLoad(int);

};

#endif // GAMEDISPLAY_H
