#ifndef TENT_H
#define TENT_H

#include <QGraphicsPixmapItem>

class Tent : public QGraphicsPixmapItem
{
private:
    int len;
    int row;
    int col;
    int x;
    int y;
public:
    Tent(int x, int y);
    // getters
    int getX();
    int getY();
    // setters
    void setX(int);
    void setY(int);
    int getRow();
    int getCol();
};

#endif // TENT_H
