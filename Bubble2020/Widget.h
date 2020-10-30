#ifndef WIDGET_H
#define WIDGET_H
#include <list>
#include <QWidget>
#include <QTimer>
#include "bomb.h"
using namespace std;
class Widget : public QWidget
{
    Q_OBJECT
private:
    int map_width = 800, map_height = 600;
    int count;
    QTimer *timer;

    struct bombStruct{
        bomb *thebomb;       //指向该炸弹的指针
        int explodeTime;    //该炸弹爆炸的时间
    };
    list<bombStruct> bombList;//炸弹列表

    //character *charList[4];//人物列表

protected:
    void paintEvent(QPaintEvent *event);
public:
    Widget(QWidget *parent = nullptr);

    bool isValid(int x, int y);
    bool placeBomb(int p, int x, int y);
    void hurtCharacter(int No, int damage);     //对编号为No的人物造成damage攻击
    ~Widget();
public slots:
    void CountPlus();
};

#endif // WIDGET_H
