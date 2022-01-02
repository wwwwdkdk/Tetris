#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QMainWindow>

class GameOver : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameOver(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
signals:

};

#endif // GAMEOVER_H
