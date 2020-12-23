#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QString>
#include <QSound>
#include <QApplication>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow *mutualUi;
    /*
     * status 取值对应状态：
     * 0 代表在初始界面
     * 1 代表进入游戏选择界面
     * 2 代表单人模式
     * 3 代表双人模式
     * 4 代表多人模式
     * 5 代表帮助界面
     */
    int status;             //表示游戏运行到哪个环节
    bool isBGM;             //表示背景音乐是否在播放
    QSound *bgm;            //背景音乐
    QPalette background;    //背景图片

private:
    Ui::MainWindow *ui;

protected:
    void paintEvent(QPaintEvent *event);//绘图事件


private slots:
    void on_pushButtonStart_clicked();
    void on_pushButtonHelp_clicked();
    void on_pushButtonQuit_clicked();
    void on_pushButtonBGM_clicked();
};
#endif // MAINWINDOW_H
