#ifndef CASTLE_H
#define CASTLE_H

#include <QGraphicsPixmapItem>

class Castle : public QGraphicsPixmapItem
{
private:
    int currHealth;
    int maxHealth;
    int x;
    int y;
public:
    Castle(int x, int y);
    // health functions
    int getCurrHealth();
    void setCurrHealth(int);
    void decrementCurrHealth(int);
    void incrementCurrHealth(int);
    // getters
    int getX();
    int getY();
    // setters
    void setX(int x);
    void setY(int y);
};

#endif // CASTLE_H
