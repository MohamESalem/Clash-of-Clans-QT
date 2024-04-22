#ifndef FENCE_H
#define FENCE_H

#include <QGraphicsPixmapItem>
#include "workersclan.h"

class Fence : public QGraphicsPixmapItem
{
private:
    int health; // currentHealth
    int maxHealth;
    int x;
    int y;
    WorkersClan* healGroup;
public:
    Fence(int x, int y);
    int getX();
    int getY();
    int getHealth();
    int getMaxHealth();
    void setHealth(int);
    void decrementHealth(int);
    void incrementHealth(int,QTimer*&,QTimer*&);
    WorkersClan* getHealGroup();
    void setHealGroup(WorkersClan*);
};

#endif // FENCE_H
