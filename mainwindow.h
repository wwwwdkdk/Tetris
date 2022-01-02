#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPainter>
#include<QKeyEvent>
#include<QTimer>
#include<QTime>
#include"gameover.h"
#include<QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void GameInit();
    void change();
    void move();
    void get_rect();
    void eliminate();
    void game_over();
    int arr[21][12];
    int flag = 0;
    int is_gameover = 0;
    int ch;
    int score = 0;
    int direction;
    int timer;
    int timer2;
    int rect;
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
