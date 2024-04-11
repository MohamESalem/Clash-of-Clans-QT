#ifndef FENCE_H
#define FENCE_H

#include <QGraphicsPixmapItem>

class Fence : public QGraphicsPixmapItem
{
private:
    int health;
public:
    Fence(int x, int y);
    int getHealth();
    void setHealth(int);
    void decrementHealth(int);
    void incrementHealth(int);
};

#endif // FENCE_H
