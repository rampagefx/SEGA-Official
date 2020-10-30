#include "widget.h"
#include "bomb.h"

#include <QApplication>
#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
