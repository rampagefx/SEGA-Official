#include <QApplication>
#include "mainwindow.h"
#include "bombqueue.h"

// Test include start
#include <QDebug>
#include "singlegame.h"
// Test include end

int main(int argc, char *argv[])
{
      QApplication a(argc, argv);
      MainWindow w;
      w.show();
      return a.exec();
//    return 0;
}
