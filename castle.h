#ifndef CASTLE_H
#define CASTLE_H

#include <QGraphicsPixmapItem>
#include "gameover.h"


class Castle : public QGraphicsPixmapItem
{
private:
    int currHealth;
    int maxHealth;
    int x;
    int y;
    gameover *o;
public:
    Castle(int x, int y);
    // health functions
    int getCurrHealth();
    void setCurrHealth(int);
    bool isCurrHealthMax();
    // getters
    int getX();
    int getY();
    // setters
    void setX(int x);
    void setY(int y);
public slots:
    void decrementCurrHealth(int);
    void incrementCurrHealth(int,QTimer*&,QTimer*&);
    void move();
};

#endif // CASTLE_H
