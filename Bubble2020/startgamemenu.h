#ifndef STARTGAMEMENU_H
#define STARTGAMEMENU_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class StartGameMenu;
}

class StartGameMenu : public QWidget
{
    Q_OBJECT

public:
    explicit StartGameMenu(QWidget *parent = nullptr);
    ~StartGameMenu();

private:
    Ui::StartGameMenu *ui;

protected:
    //void paintEvent(QPaintEvent *event);//绘图事件

private slots:
    void on_pushButtonBGMstart_clicked();
    void on_pushButtonBackstart_clicked();
    void on_pushButtonMulti_clicked();
    void on_pushButtonSingle_clicked();
    void on_pushButtonDouble_clicked();
};

#endif // STARTGAMEMENU_H
