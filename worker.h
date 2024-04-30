#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QGraphicsPixmapItem>

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

public slots:
    void move();
    void returnBack();
};

#endif // WORKER_H
