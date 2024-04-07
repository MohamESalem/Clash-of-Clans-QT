#ifndef CANNON_H
#define CANNON_H

#include <QGraphicsPixmapItem>
#include <QMouseEvent>

class Cannon : public QGraphicsPixmapItem
{
private:
    int x;
    int y;
public:
    Cannon(int x, int y);
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
};

#endif // CANNON_H
