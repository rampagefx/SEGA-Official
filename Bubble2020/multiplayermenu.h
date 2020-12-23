#ifndef MULTIPLAYERMENU_H
#define MULTIPLAYERMENU_H

#include <QWidget>
#include "mainwindow.h"
#include "multigame.h"

namespace Ui {
class multiplayermenu;
}

class multiplayermenu : public QWidget
{
    Q_OBJECT

public:
    explicit multiplayermenu(QWidget *parent = nullptr);
    ~multiplayermenu();

private slots:
    void on_creatgame_clicked();

    void on_joingame_clicked();

    void on_multiback_clicked();

private:
    Ui::multiplayermenu *ui;
};

#endif // MULTIPLAYERMENU_H
