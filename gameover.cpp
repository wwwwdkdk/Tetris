#include "gameover.h"
#include<QPainter>
#include<QPushButton>
#include<mainwindow.h>

GameOver::GameOver(QWidget *parent) : QMainWindow(parent) {
    setFixedSize(500, 600);
    setWindowTitle("游戏结束");
    QPushButton *btn_start = new QPushButton(this);
    QPushButton *btn_exit = new QPushButton(this);
    btn_start->setFixedSize(200, 60);
    btn_exit->setFixedSize(200, 60);
    btn_start->setText("重新开始");
    btn_start->setStyleSheet("QPushButton{border-radius:10px;background:#404040}");
    btn_exit->setText("退出游戏");
    btn_exit->setStyleSheet("QPushButton{border-radius:10px;background:#404040}");
    btn_start->move(150, 400);
    btn_exit->move(150, 480);
    connect(btn_exit, &QPushButton::clicked, this, [=]() {
        this->close();
    });
    connect(btn_start, &QPushButton::clicked, this, [=]() {
        this->close();
        MainWindow *q = new MainWindow;
        q->show();
    });
}

void GameOver::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(QRect(0, 0, 500, 600), QPixmap(":/background.png"));
    painter.drawPixmap(QRect(50, 0, 500, 200), QPixmap(":/gameover.png"));
}
