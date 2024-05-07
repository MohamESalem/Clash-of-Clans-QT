#ifndef CANNON_H
#define CANNON_H

#include <QGraphicsPixmapItem>
#include <QMouseEvent>

class Cannon : public QGraphicsPixmapItem
{
private:
    int x;
    int y;
    int numBullets;
public:
    Cannon(int,int);
    int getX();
    int getY();
    int getNumBullets();
    void setX(int);
    void setY(int);
    void setNumBullets(int);
};

#endif // CANNON_H
