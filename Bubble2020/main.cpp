#include <QApplication>
#include "mainwindow.h"
#include "bombqueue.h"

// Test include start
#include <QDebug>
#include "singlegame.h"
// Test include end

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
    QApplication a(argc, argv);
    SingleGame w;
    w.show();
    return a.exec();
}
