#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <list>
#include "character.h"

class SingleGame : public QWidget
{
    Q_OBJECT
private:
    QTimer *timer;
    int frame;
    int** map;
    Character *player;
    std::list<Character> enemy;
public:
    explicit SingleGame(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

signals:

public slots:
    void frame_plus();
};

#endif // SINGLEGAME_H
