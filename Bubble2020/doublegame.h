#ifndef DOUBLEGAME_H
#define DOUBLEGAME_H

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QLabel>
#include <QImage>
#include <QPoint>
#include <QLCDNumber>
#include <QProgressBar>
#include <QPushButton>
#include "character.h"
#include "bomb.h"
#include "bombqueue.h"
#include "npc.h"
#ifndef SINGLEGAME_H
const int windows_size_x = 1286; // 窗口尺寸
const int windows_size_y = 730;
const int map_size_x = 20; // 地图尺寸（格子数量）
const int map_size_y = 20;
const int pic_size_x = 35; // 图片尺寸（像素）
const int pic_size_y = 35;
const int enemy_num = 5; // AI的数量
#endif
namespace Ui {
class DoubleGame;
}

class DoubleGame : public QWidget
{
    Q_OBJECT
private:
    QTimer *timer;
    int frame;
    int** map;
    int GameStatus;
    Character *player[2];
    npc *enemys[enemy_num];
    QLabel *map_pic[map_size_y][map_size_x];
    QLabel *LabelPicturePause;
    QLabel *character_pic, *character_name;
    QLabel *player_profile[2];
    QLabel *discription[3];
    QLabel *game_back;
    QImage map_image[6];
    QImage character_image[2];
    QImage enemy_image;
    QImage player_image[2];
    QImage background_image;
//    QImage bomb_image;
    QPushButton *next_level;
    QPoint start_point = QPoint(50+276, 50);
    QLCDNumber *HP_show[2];
    QProgressBar *CD_display[2];
    BombQueue bomb_queue;
public:
    explicit DoubleGame(int[], QWidget *parent = nullptr);
    // TODO
    bool PlaceBomb(int p, int x, int y);
    bool isValid(int x, int y); // out of map or not
    int explode();
signals:
    void GameOver(int player_id);
    void GamePass(int player_id);
protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void MapLoad(int);

signals:

public slots:
    void frame_plus();
    void next_game();
};

#endif // DOUBLEGAME_H
