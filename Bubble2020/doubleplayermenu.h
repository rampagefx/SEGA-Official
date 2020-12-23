#ifndef DOUBLEPLAYERMENU_H
#define DOUBLEPLAYERMENU_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class DoublePlayerMenu;
}

class DoublePlayerMenu : public QWidget
{
    Q_OBJECT

public:
    explicit DoublePlayerMenu(QWidget *parent = nullptr);
    ~DoublePlayerMenu();
    //两个角色的选择
    int player1_status;
    int player2_status;
protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::DoublePlayerMenu *ui;

private slots:
    void on_pushButtonBackchoose_clicked();
    void on_pushButtonBGMsingle_clicked();
    void on_pushButtonNotDecide1_clicked();
    void on_pushButtonNotDecide2_clicked();
    void on_pushButtonDecide_clicked();
    void on_pushButtonCharacter1_1_clicked();
    void on_pushButtonCharacter1_2_clicked();
    void on_pushButtonCharacter1_3_clicked();
    void on_pushButtonCharacter2_1_clicked();
    void on_pushButtonCharacter2_2_clicked();
    void on_pushButtonCharacter2_3_clicked();

};

#endif // DOUBLEPLAYERMENU_H
