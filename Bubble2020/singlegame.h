#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <list>
#include "character.h"
#include "bomb.h"

const int windows_size_x = 800;
const int windows_size_y = 800;
const int map_size_x = 20;
const int map_size_y = 20;

class SingleGame : public QWidget
{
    Q_OBJECT
private:
    QTimer *timer;
    int frame;
    int** map;
    Character *player;

public:
    explicit SingleGame(QWidget *parent = nullptr);
    // TODO
    bool PlaceBomb(int p, int x, int y);
    bool isValid(int x, int y); // out of map or not
    int hurtCharacter(int x, int y);
protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

signals:

public slots:
    void frame_plus();
};


#endif // SINGLEGAME_H
