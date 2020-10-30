#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <list>
#include "character.h"
#include "bomb.h"

class SingleGame : public QWidget
{
    Q_OBJECT
private:
    QTimer *timer;
    int frame;
    int** map;
    int map_width = 800, map_height = 600;
    struct bombStruct{
        bomb *thebomb;
        int explodeTime;
    };
    bombStruct *bombList[1000];
    int bombList_header, bombList_tailer;
    Character *charList[4];
    std::list<Character> enemy;
public:
    explicit SingleGame(QWidget *parent = nullptr);
    bool isValid(int x, int y);
    bool placeBomb(int p, int x, int y);
    void hurtCharacter(int No, int damage);
protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

signals:

public slots:
    void frame_plus();
};


#endif // SINGLEGAME_H
