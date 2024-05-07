#ifndef CASTLE_H
#define CASTLE_H

#include <QGraphicsPixmapItem>
#include "healthbar.h"

class Castle : public QGraphicsPixmapItem
{
private:
    int currHealth;
    int maxHealth;
    int x;
    int y;
    HealthBar* healthBar;
    bool isShielded;
    bool finished;
public:
    Castle(int,int);
    // health functions
    int getCurrHealth();
    void setCurrHealth(int);
    bool isCurrHealthMax();
    void shield();
    void removeShield();
    // getters
    int getX();
    int getY();
    bool getIsShielded();
    // setters
    void setX(int);
    void setY(int);
    void setIsShielded(bool);
    int row = 6;
    int col = 7;

public slots:
    void decrementCurrHealth(int);
    void incrementCurrHealth(int);
    void move();
};

#endif // CASTLE_H
