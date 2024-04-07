#ifndef FENCE_H
#define FENCE_H

#include <QGraphicsPixmapItem>

class Fence : public QGraphicsPixmapItem
{
private:
    int health;
public:
    Fence(int x, int y);
    void setHealth(int);
    void decrementHealth(int);
    void incrementHealth(int);
    int getHealth();
};

#endif // FENCE_H
