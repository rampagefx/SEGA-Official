#ifndef SINGLEPLAYERMENU_H
#define SINGLEPLAYERMENU_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class SinglePlayerMenu;
}

class SinglePlayerMenu : public QWidget
{
    Q_OBJECT

public:
    explicit SinglePlayerMenu(QWidget *parent = nullptr);
    ~SinglePlayerMenu();

private:
    Ui::SinglePlayerMenu *ui;

private slots:
    void on_pushButtonBackchoose_clicked();
    void on_pushButtonBGMsingle_clicked();
    void on_pushButtonNotDecide_clicked();
    void on_pushButtonDecide_clicked();
    void on_pushButtonCharacter1_clicked();
    void on_pushButtonCharacter2_clicked();
    void on_pushButtonCharacter3_clicked();
};

#endif // SINGLEPLAYERMENU_H
