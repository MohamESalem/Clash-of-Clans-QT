#include "fence.h"
#include "game.h"
#include "worker.h"

extern Game* game;

Fence::Fence(int x, int y) {
    QPixmap fenceImg(":/images/img/fence.png");
    fenceImg = fenceImg.scaled(game->getBlockUnit(), game->getBlockUnit());
    setPixmap(fenceImg);
    this->x = x;
    this->y = y;
    setPos(this->x, this->y);
    maxHealth = 60;
    health = maxHealth;
    healGroup = NULL;
}

int Fence::getX() {return x;}
int Fence::getY() {return y;}

void Fence::setHealth(int x)
{
    health = x;
}

void Fence::decrementHealth(int x)
// PASS THEM BE REFERENCE FOR ENEMY DAMAGING FENCE
// LOOK AT DECREMENTHEALTH() IN CASTLE CLASS
{
    health -= x;

    if(health > 0) {
        if(healGroup == NULL) {
            int ava = game->getAvailableGroup(this->x, this->y);
            // qDebug() << "ava = " << ava << '\n';
            if(ava == 1) {
                healGroup = game->getGroup1();
                healGroup->changeAvailability(false);
                healGroup->createWorkers(this->x, this->y);
            } else if(ava == 2) {
                healGroup = game->getGroup2();
                healGroup->changeAvailability(false);
                healGroup->createWorkers(this->x, this->y);
            } else if(ava == 0) {
                if(!game->damagedFence.contains(this)) {
                    game->damagedFence.append(this);
                }
            } // otherwise ava = -1, i.e., no group are availble, don't do anything
        }
    }
    else {
        // enemy destroys the fence when the fence's health goes below zero
        scene()->removeItem(this);
        if(healGroup) healGroup->changeAvailability(true);
        delete this;
        return;
    }
}


void Fence::incrementHealth(int x, QTimer*& returnTimer, QTimer*& healTimer)
{
    Worker* w = dynamic_cast<Worker*>(returnTimer->parent());

    if(health == maxHealth) {
        healTimer->stop();
        returnTimer->start(250);
    } else if(health + x < maxHealth) {
        health += x;
        // qDebug() << "Improving Health\n";
    }
    else {

        health = maxHealth;
        // qDebug() << "health is maximum";
        healGroup = NULL;

        // code to check if there are other damaged fences before returning back
        if(!game->damagedFence.isEmpty()) {
            // qDebug() << "Heading to a new fence\n";
            Fence* f = game->damagedFence.first();
            f->setHealGroup(w->getGroup());
            f->getHealGroup()->createWorkers(f->getX(), f->getY());
            game->damagedFence.removeFirst();
        } else {
            w->getGroup()->changeAvailability(true);
        }

        healTimer->stop();
        returnTimer->start(250);
    }
}

int Fence::getHealth() {return health;}
int Fence::getMaxHealth() {return maxHealth;}
WorkersClan* Fence::getHealGroup() {return healGroup;}
void Fence::setHealGroup(WorkersClan* g) {healGroup = g;}
