#ifndef WORKERSCLAN_H
#define WORKERSCLAN_H

#include <QObject>
#include "tent.h"
#include "worker.h"

class WorkersClan : public QObject
{
    Q_OBJECT
private:
    bool isAvailable;
    std::vector<bool> isAlive;
    std::vector<Worker*> workers;
    Tent* tent;
    size_t numKilled;
    int detX;
    int detY;

public:
    bool isAllClanDead;
    WorkersClan(int,Tent*);
    void createWorkers(int,int);
    bool getAvailability();
    bool getIsAllClanDead();
    Tent* getTent();
    void changeAvailability(bool);
    void changeIsAlive(int);
    void changeWorkerPointerToNULL(int i);
    int getDetX();
    int getDetY();
    void setDetX(int);
    void setDetY(int);
};

#endif // WORKERSCLAN_H
