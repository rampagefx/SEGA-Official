#ifndef DOUBLEGAME_H
#define DOUBLEGAME_H

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QLabel>
#include <QImage>
#include <QPoint>
#include "character.h"
#include "bomb.h"
#include "bombqueue.h"
#include "npc.h"

#ifndef SINGLEGAME_H
const int windows_size_x = 800;
const int windows_size_y = 800;
const int map_size_x = 20;
const int map_size_y = 20;
const int pic_size_x = 35;
const int pic_size_y = 35;
const int enemy_num = 5;
#endif

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
    QImage map_image[2];
    QImage character_image[2];
    QImage enemy_image;
    QImage bomb_image;
    QPoint start_point = QPoint(50, 50);
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
    void MapLoad();

signals:

public slots:
    void frame_plus();
};

#endif // DOUBLEGAME_H
