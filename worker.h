#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "graph.h"

class WorkersClan;
class Fence;

class Worker : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int imgLen;
    int healAbility;
    QTimer* moveTimer;
    QTimer* healTimer;
    QTimer* returnTimer;
    QTimer* healAnimationTimer;
    QStringList healImgs;
    QStringList dieImgs;
    WorkersClan* group;
    int clanIndex;
    bool finished;
    std::vector<Node*> path;
    int curr;
    int offsetX;
    int offsetY;
    double STEP_SIZE;

public:
    Worker(WorkersClan* g, int index);
    int getHealAbility();
    void setHealAbility(int);
    WorkersClan* getGroup();
    QTimer* getHealAnimationTimer();
    int getClanIndex();
    void healFence(Fence*);
    void die();
    bool isFinished();
    void changePath(int x, int y);

public slots:
    void move();
    void returnBack();
};

#endif // WORKER_H
