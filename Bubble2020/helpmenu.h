#ifndef HELPMENU_H
#define HELPMENU_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class HelpMenu;
}

class HelpMenu : public QWidget
{
    Q_OBJECT

public:
    explicit HelpMenu(QWidget *parent = nullptr);
    ~HelpMenu();

private:
    Ui::HelpMenu *ui;

protected:
    //void paintEvent(QPaintEvent *event);//绘图事件

private slots:
    void on_pushButtonBGMhelp_clicked();
    void on_pushButtonBackhelp_clicked();
    void on_pushButtonBackground_clicked();
    void on_pushButtonIntro_clicked();
    void on_pushButtonCharacter_clicked();
    void on_pushButtonreturn_clicked();
};

#endif // HELPMENU_H
