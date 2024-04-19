#include "workersclan.h"
#include "worker.h"
#include "game.h"

extern Game* game;

WorkersClan::WorkersClan(int n, Tent* tent) {
    // initialize the vectors
    isAlive.resize(n);
    for(auto b : isAlive) b = 1;
    workers.resize(n);
    for(size_t i = 0; i < workers.size(); i++) workers[i] = NULL;
    // initialize data members
    isAvailable = true;
    isAllClanDead = false;
    this->tent = tent;
    numKilled = 0;
}

void WorkersClan::createWorkers(int x, int y) {
    setDetX(x);
    setDetY(y);
    for(size_t i = 0; i < isAlive.size(); i++) {
        if(isAlive[i]) {
            if(workers[i] == NULL) {
                Worker* w = new Worker(this, i);
                workers[i] = w;
                game->getScene()->addItem(w);
                if(i != isAlive.size() - 1) game->delay(2);
            } // else {
                // workers[i]->setDetX(x);
                // workers[i]->setDetY(y);
            // }
        }

    }
}

bool WorkersClan::getAvailability() {return isAvailable;}
void WorkersClan::changeAvailability(bool b) {
    isAvailable = b;
}

void WorkersClan::changeIsAlive(int i) {
    isAlive[i] = false;
    numKilled++;
    changeWorkerPointerToNULL(i);
    if(numKilled == workers.size()) {changeAvailability(false); isAllClanDead = true;}
}

void WorkersClan::changeWorkerPointerToNULL(int i)
{
    workers[i] = NULL;
}

Tent* WorkersClan::getTent() {return tent;}
bool WorkersClan::getIsAllClanDead() {return isAllClanDead;}
int WorkersClan::getDetX() {return detX;}
int WorkersClan::getDetY() {return detY;}
void WorkersClan::setDetX(int x) {detX = x;}
void WorkersClan::setDetY(int y) {detY = y;}
