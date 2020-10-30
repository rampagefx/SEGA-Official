#include "Widget.h"
#include <QPainter>
#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(CountPlus()));
    connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
    timer->start(200);
    count = 0;

}
void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawLine(1, 1, count, count);
}
void Widget::CountPlus()
{
    if (count < 300)
        count+=10;
}
Widget::~Widget()
{

}

bool Widget::isValid(int x, int y){
    if (x>=0 && x<map_width && y>=0 && y<map_height) return true;
    else return false;
}

bool Widget::placeBomb(int p, int x, int y){
    bomb *newBomb = new bomb();
    newBomb->Set(p, x, y);
    bombStruct *newStruct = new bombStruct{newBomb, count};
}
