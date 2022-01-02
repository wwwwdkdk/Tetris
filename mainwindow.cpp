#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->resize(500, 600);
    this->setWindowTitle("俄罗斯方块");
    GameInit();
    timer = startTimer(300);
    timer2 = startTimer(100);
    QPushButton *btn_exit = new QPushButton(this);
    btn_exit->setStyleSheet("QPushButton{border-radius:10px;background:#404040}");
    btn_exit->setFixedSize(150, 50);
    btn_exit->setText("退出游戏");
    btn_exit->move(330, 450);
    connect(btn_exit, &QPushButton::clicked, this, [=]() {
        this->close();
    });
}

MainWindow::~MainWindow() {
    delete ui;
}

/*绘图事件*/
void MainWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(QRect(0, 0, 500, 600), QPixmap(":/background.png"));
    painter.setPen(QPen(Qt::white));
    painter.setBrush(Qt::black);
    //绘制分界线
    for (int i = 0; i < 20; i++) {
        for (int j = 1; j < 11; j++) {
            if (arr[i][j] == 1 || arr[i][j] == 2) {
                painter.drawRect((j - 1) * 30, i * 30, 30, 30);
            }
        }
        painter.drawRect(300, i * 30, 10, 30);
    }
    painter.setPen(QPen(Qt::black));
    painter.setFont(QFont("Times", 30, QFont::Bold));
    painter.drawText(350, 100, "得分:");
    painter.setPen(QPen(Qt::red));
    painter.drawText(450, 100, QString::number(score));
}

/*生成不同形状的砖块*/
void MainWindow::get_rect() {
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    rect = 1 + qrand() % 7; //随机生成方块
    if (flag == 0) {
        switch (rect) {
            case 1:
                arr[0][4] = 1;//====
                arr[0][5] = 1;
                arr[0][6] = 1;
                arr[0][7] = 1;
                direction = 1;
                break;
            case 2:
                arr[0][4] = 1;//===
                arr[0][5] = 1;// =
                arr[0][6] = 1;
                arr[1][5] = 1;
                direction = 2;
                break;
            case 3:
                arr[0][4] = 1;//===
                arr[0][5] = 1;//  =
                arr[0][6] = 1;
                arr[1][6] = 1;
                direction = 3;
                break;
            case 4:
                arr[0][4] = 1;//==
                arr[0][5] = 1;// ==
                arr[1][5] = 1;
                arr[1][6] = 1;
                direction = 4;
                break;
            case 5:
                arr[0][5] = 1;// ==
                arr[0][6] = 1;//==
                arr[1][4] = 1;
                arr[1][5] = 1;
                direction = 5;
                break;
            case 6:
                arr[0][5] = 1;//==
                arr[0][6] = 1;//==
                arr[1][5] = 1;
                arr[1][6] = 1;
                direction = 6;
                break;
            case 7:
                arr[0][4] = 1;//=
                arr[1][4] = 1;//===
                arr[1][5] = 1;
                arr[1][6] = 1;
                direction = 7;
                break;
        }
        flag = 1;
    }
}

void MainWindow::timerEvent(QTimerEvent *event) {
    if (event->timerId() == timer) {
        get_rect();
        eliminate();
        move();
        game_over();
    }
    if (event->timerId() == timer2) {
        change();
    }
}

/*方块移动*/
void MainWindow::move() {
    int flag2 = 0;
    //判断周围是否有方块
    for (int i = 20; i >= 0 && flag2 == 0; i--) {
        for (int j = 10; j >= 1; j--) {
            if (arr[i][j] == 2) {
                if (arr[i - 1][j] == 1) {
                    for (int i = 0; i < 20; i++) {
                        for (int j = 1; j < 11; j++) {
                            if (arr[i][j] == 1) {
                                arr[i][j] = 2;
                            }
                        }
                    }
                    flag = 0;
                    flag2 = 1;
                    break;
                }
            }
        }
    }
    for (int i = 18; i >= 0 && flag2 == 0; i--) {
        for (int j = 10; j >= 1; j--) {
            if (arr[i][j] == 1) {
                arr[i][j] = 0;
                arr[i + 1][j] = 1;
            }
        }
    }
    update();
}

/*根据键盘输入的不同改变方块的形态*/
void MainWindow::change() {
    int flag1 = 0;
    int flag2 = 0;
    int flag3 = 0;
    switch (ch) {
        case 72:
            switch (direction) {
                case 1:
                    for (int i = 0; i < 20 && flag3 == 0; i++) {
                        for (int j = 1; j < 11; j++) {
                            if (arr[i][j] == 1 && arr[i][j + 1] == 1) {
                                arr[i][j] = 0;
                                arr[i][j + 1] = 0;
                                arr[i][j + 2] = 0;
                                arr[i][j + 3] = 0;
                                arr[i - 1][j + 2] = 1;
                                arr[i][j + 2] = 1;
                                arr[i + 1][j + 2] = 1;
                                arr[i + 2][j + 2] = 1;
                                flag3 = 1;
                                break;
                            } else if (arr[i][j] == 1 && arr[i][j + 1] != 1) {
                                if (j < 3 || j > 8) {
                                    flag3 = 1;
                                    break;
                                }
                                arr[i][j] = 0;
                                arr[i + 1][j] = 0;
                                arr[i + 2][j] = 0;
                                arr[i + 3][j] = 0;
                                arr[i + 1][j - 2] = 1;
                                arr[i + 1][j - 1] = 1;
                                arr[i + 1][j] = 1;
                                arr[i + 1][j + 1] = 1;
                                flag3 = 1;
                                break;
                            }
                        }
                    }
                    break;
                case 2:
                    for (int i = 0; i < 20 && flag3 == 0; i++) {
                        for (int j = 1; j < 11; j++) {
                            if (arr[i][j] == 1 && arr[i][j + 1] == 1) {
                                arr[i][j + 2] = 0;
                                arr[i - 1][j + 1] = 1;
                                flag3 = 1;
                                break;
                            } else if (arr[i][j] == 1 && arr[i + 1][j - 1] == 1 && arr[i + 2][j] == 1) {
                                if (j >= 10) {
                                    flag3 = 1;
                                    break;
                                }
                                arr[i + 2][j] = 0;
                                arr[i + 1][j + 1] = 1;
                                flag3 = 1;
                                break;
                            } else if (arr[i][j] == 1 && arr[i + 1][j - 1] == 1 && arr[i + 1][j + 1] == 1) {
                                arr[i + 1][j - 1] = 0;
                                arr[i + 2][j] = 1;
                                flag3 = 1;
                                break;
                            } else if (arr[i][j] == 1 && arr[i + 1][j - 1] != 1 && arr[i][j + 1] != 1) {
                                if (j < 2) {
                                    flag3 = 1;
                                    break;
                                }
                                arr[i][j] = 0;
                                arr[i + 1][j - 1] = 1;
                                flag3 = 1;
                                break;
                                
                            }
                        }
                    }
                    break;
                case 3:
                    for (int i = 0; i < 20 && flag3 == 0; i++) {
                        for (int j = 1; j < 11; j++) {
                            if (arr[i][j] == 1 && arr[i + 1][j] != 1) {
                                arr[i][j] = 0;
                                arr[i][j + 1] = 0;
                                arr[i + 1][j + 1] = 1;
                                arr[i - 1][j + 2] = 1;
                                flag3 = 1;
                                break;
                            } else if (arr[i][j] == 1 && arr[i + 2][j - 1] == 1) {
                                if (j >= 10) {
                                    flag3 = 1;
                                    break;
                                }
                                arr[i][j] = 0;
                                arr[i + 1][j] = 0;
                                arr[i + 1][j - 1] = 1;
                                arr[i + 2][j + 1] = 1;
                                flag3 = 1;
                                break;
                            } else if (arr[i][j] == 1 && arr[i + 1][j + 1] == 1) {
                                
                                arr[i + 1][j + 1] = 0;
                                arr[i + 1][j + 2] = 0;
                                arr[i - 1][j] = 1;
                                arr[i - 1][j + 1] = 1;
                                flag3 = 1;
                                break;
                            } else if (arr[i][j] == 1 && arr[i][j - 1] != 1 && arr[i][j + 1] == 1) {
                                if (j < 2) {
                                    flag3 = 1;
                                    break;
                                }
                                arr[i][j] = 0;
                                arr[i][j + 1] = 0;
                                arr[i + 2][j] = 0;
                                arr[i + 1][j - 1] = 1;
                                arr[i + 1][j + 1] = 1;
                                arr[i + 2][j + 1] = 1;
                                flag3 = 1;
                                break;
                            }
                        }
                    }
                    break;
                case 4:
                    for (int i = 0; i < 20 && flag3 == 0; i++) {
                        for (int j = 1; j < 11; j++) {
                            if (arr[i][j] == 1 && arr[i + 1][j] != 1) {
                                arr[i][j] = 0;
                                arr[i + 1][j + 2] = 0;
                                arr[i - 1][j + 2] = 1;
                                arr[i][j + 2] = 1;
                                flag3 = 1;
                                break;
                            } else if (arr[i][j] == 1 && arr[i + 1][j] == 1) {
                                if (j < 3) {
                                    flag3 = 1;
                                    break;
                                }
                                arr[i][j] = 0;
                                arr[i + 1][j] = 0;
                                arr[i + 1][j - 2] = 1;
                                arr[i + 2][j] = 1;
                                flag3 = 1;
                                break;
                            }
                        }
                    }
                    break;
                case 5:
                    for (int i = 0; i < 20 && flag3 == 0; i++) {
                        for (int j = 1; j < 11; j++) {
                            if (arr[i][j] == 1 && arr[i][j + 1] == 1) {
                                arr[i + 1][j - 1] = 0;
                                arr[i + 1][j] = 0;
                                arr[i - 1][j] = 1;
                                arr[i + 1][j + 1] = 1;
                                flag3 = 1;
                                break;
                            } else if (arr[i][j] == 1 && arr[i][j + 1] != 1) {
                                if (j < 2) {
                                    flag3 = 1;
                                    break;
                                }
                                arr[i][j] = 0;
                                arr[i + 2][j + 1] = 0;
                                arr[i + 2][j] = 1;
                                arr[i + 2][j - 1] = 1;
                                flag3 = 1;
                                break;
                            }
                        }
                    }
                    break;
                case 6:
                    break;
                case 7:
                    for (int i = 0; i < 20 && flag3 == 0; i++) {
                        for (int j = 1; j < 11; j++) {
                            if (arr[i][j] == 1 && arr[i + 1][j] != 1) {
                                arr[i][j] = 0;
                                arr[i][j + 1] = 0;
                                arr[i + 1][j + 1] = 1;
                                arr[i - 1][j + 2] = 1;
                                flag3 = 1;
                                break;
                            } else if (arr[i][j] == 1 && arr[i + 2][j - 1] == 1) {
                                if (j >= 10) {
                                    flag3 = 1;
                                    break;
                                }
                                arr[i][j] = 0;
                                arr[i + 1][j] = 0;
                                arr[i + 1][j - 1] = 1;
                                arr[i + 2][j + 1] = 1;
                                flag3 = 1;
                                break;
                            } else if (arr[i][j] == 1 && arr[i + 1][j + 1] == 1) {
                                
                                arr[i + 1][j + 1] = 0;
                                arr[i + 1][j + 2] = 0;
                                arr[i - 1][j] = 1;
                                arr[i - 1][j + 1] = 1;
                                flag3 = 1;
                                break;
                            } else if (arr[i][j] == 1 && arr[i][j - 1] != 1 && arr[i][j + 1] == 1) {
                                if (j < 2) {
                                    flag3 = 1;
                                    break;
                                }
                                arr[i][j] = 0;
                                arr[i][j + 1] = 0;
                                arr[i + 2][j] = 0;
                                arr[i + 1][j - 1] = 1;
                                arr[i + 1][j + 1] = 1;
                                arr[i + 2][j + 1] = 1;
                                flag3 = 1;
                                break;
                            }
                        }
                    }
                    break;
                    break;
            }
            break;
        case 75:
            for (int i = 19; i >= 0 && flag1 == 0; i--) {
                for (int j = 11; j >= 1; j--) {
                    if (arr[i][j] == 1) {
                        if (arr[i][j - 1] == 2 || arr[i][j - 1] == 3) {
                            flag1 = 1;
                            break;
                        }
                    }
                }
            }
            for (int i = 19; i >= 0 && flag1 == 0; i--) {
                for (int j = 1; j < 11; j++) {
                    if (arr[i][j] == 1) {
                        arr[i][j] = 0;
                        arr[i][j - 1] = 1;
                    }
                    
                }
            }
            break;
        case 77:
            for (int i = 19; i >= 0 && flag2 == 0; i--) {
                for (int j = 11; j >= 1; j--) {
                    if (arr[i][j] == 1) {
                        if (arr[i][j + 1] == 2 || arr[i][j + 1] == 3) {
                            flag2 = 1;
                            break;
                        }
                    }
                    
                }
            }
            for (int i = 19; i >= 0 && flag2 == 0; i--) {
                for (int j = 11; j >= 1; j--) {
                    if (arr[i][j] == 1) {
                        arr[i][j] = 0;
                        arr[i][j + 1] = 1;
                    }
                }
            }
            break;
        case 80:
            while (flag == 1) {
                move();
            }
            break;
    }
    update();
    
    ch = 0;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case (Qt::Key_Up):
            ch = 72;
            break;
        case (Qt::Key_Down):
            ch = 80;
            break;
        case (Qt::Key_Left):
            ch = 75;
            break;
        case (Qt::Key_Right):
            ch = 77;
            break;
    }
}

void MainWindow::GameInit() {
    for (int i = 0; i < 20; i++) {
        for (int j = 1; j < 11; j++) {
            arr[i][j] = 0;
        }
    }
    for (int i = 1; i < 11; i++) {
        arr[20][i] = 2;
    }
    for (int i = 0; i < 20; i++) {
        arr[i][0] = 3;
        arr[i][11] = 3;
    }
}

void MainWindow::eliminate() {
    for (int i = 19; i >= 0; i--) { //判断当前行是否全为2
        if (arr[i][6] + arr[i][1] + arr[i][2] + arr[i][3] + arr[i][4] + arr[i][5] + arr[i][7] + arr[i][8] + arr[i][9] +
            arr[i][10] == 20) {
            //设置为0（清除全行）
            arr[i][6] = arr[i][1] = arr[i][2] = arr[i][3] = arr[i][4] = arr[i][5] = arr[i][7] = arr[i][8] = arr[i][9] = arr[i][10] = 0;
            //因为底部消除了一行，将上方的所有行下移一行
            for (int n = i - 1; n >= 0; n--) {
                for (int j = 10; j >= 1; j--) {
                    if (arr[n][j] == 2) {
                        arr[n][j] = 0;
                        arr[n + 1][j] = 2;
                    }
                }
            }
            score += 10;//加分
        }
    }
}

void MainWindow::game_over() {
    for (int i = 1; i < 11; i++) {
        if (arr[0][i] == 2) {
            killTimer(timer);
            killTimer(timer2);
            QTimer::singleShot(500, this, [=]() {
                this->close();
                GameOver *g = new GameOver;
                g->show();
            });
            break;
        }
    }
}
