#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QLabel>
#include <QImage>
#include <QPoint>
#include <QLCDNumber>
#include "character.h"
#include "bomb.h"
#include "bombqueue.h"
#include "npc.h"
const int windows_size_x = 800; // 窗口尺寸
const int windows_size_y = 800;
const int map_size_x = 20; // 地图尺寸（格子数量）
const int map_size_y = 20;
const int pic_size_x = 35; // 图片尺寸（像素）
const int pic_size_y = 35;
const int enemy_num = 5; // AI的数量
namespace Ui {
class SingleGame;
}
// 单人游戏窗口
class SingleGame : public QWidget
{
    Q_OBJECT
private:
    Ui::SingleGame *ui;
    QTimer *timer;
    int frame;
    int** map;
    int GameStatus;
    Character *player;
    npc *enemys[enemy_num];
    QLabel *map_pic[map_size_y][map_size_x];
    QLabel *LabelPicturePause;
    QLabel *character_pic, *character_name;
    QImage map_image[5];
    QImage character_image;
    QImage enemy_image;
//    QImage bomb_image;
    QPoint start_point = QPoint(50, 50);
    QLCDNumber *CD_show;
    BombQueue bomb_queue;
public:
    explicit SingleGame(int, QWidget *parent = nullptr);
    // TODO
    bool PlaceBomb(int p, int x, int y);
    bool isValid(int x, int y); // out of map or not
    int explode();
signals:
    void GameOver();
    void GamePass();
protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void MapLoad(int);

signals:

public slots:
    void frame_plus();
};


#endif // SINGLEGAME_H
