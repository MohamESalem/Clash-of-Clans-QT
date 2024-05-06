#ifndef FENCE_H
#define FENCE_H

#include <QGraphicsPixmapItem>
#include "workersclan.h"
#include "healthbar.h"

class Fence : public QGraphicsPixmapItem
{
private:
    int health; // currentHealth
    int maxHealth;
    int x;
    int y;
    WorkersClan* healGroup;
    HealthBar* healthBar;
    bool isHealthBarShown;
    bool finished;
public:
    Fence(int x, int y);
    int getX();
    int getY();
    int getHealth();
    int getMaxHealth();
    void setHealth(int);
    void decrementHealth(int,QTimer*&,QTimer*&,QTimer*&);
    void decrementHealth(int);

    void incrementHealth(int,QTimer*&,QTimer*&);
    WorkersClan* getHealGroup();
    void setHealGroup(WorkersClan*);
    bool isFinished();
    // TEST
};

#endif // FENCE_H
