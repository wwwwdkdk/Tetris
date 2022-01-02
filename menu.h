#ifndef MENU_H
#define MENU_H

#include <QMainWindow>

class Menu : public QMainWindow {
    Q_OBJECT
public:
    explicit Menu(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    signals:
    
};

#endif // MENU_H
