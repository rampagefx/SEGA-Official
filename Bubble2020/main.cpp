#include <QApplication>
#include "mainwindow.h"
#include "bombqueue.h"

// Test include start
#include <QDebug>
#include "singlegame.h"
#include "doublegame.h"

// Test include end

int main(int argc, char *argv[])
{
      QApplication a(argc, argv);
      int player_id[2] = {0,0};
      DoubleGame *w = new DoubleGame(player_id, nullptr);
      w->show();
      // SingleGame w(0, nullptr);
      // w.show();
      // MainWindow w;
      // w.show();
      return a.exec();
//    return 0;
}
