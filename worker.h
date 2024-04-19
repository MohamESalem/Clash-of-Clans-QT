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
    int healAbility;
    QTimer* moveTimer;
    QTimer* healTimer;
    QTimer* returnTimer;
    WorkersClan* group;
    int clanIndex;

public:
    Worker(WorkersClan* g, int index);
    int getHealAbility();
    void setHealAbility(int);
    WorkersClan* getGroup();
    int getClanIndex();
    void healFence(Fence*);

public slots:
    void move();
    void returnBack();
};

#endif // WORKER_H
