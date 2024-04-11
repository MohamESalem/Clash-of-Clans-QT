#include "enemy.h"
#include "game.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>
#include <QDebug>
#include <QGraphicsScene>
#include "fence.h"
#include "worker.h"

extern Game* game;

Enemy::Enemy(int x, int y)
{
    QPixmap enemyImg(":/images/img/enemy.png");
    enemyImg = enemyImg.scaled(game->getBlockUnit(), game->getBlockUnit());
    setPixmap(enemyImg);
    setTransformOriginPoint(game->getBlockUnit()/2.0,game->getBlockUnit()/2.0);
    setPos(x,y);
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveRandomly()));
    timer->start(50);
    health = 60;
}

void Enemy::moveRandomly()
{
    QList<QGraphicsItem *> collided_items = collidingItems();
    foreach(auto& item, collided_items) {
        if(typeid(*item) == typeid(Fence)) {
            // remove the item from the scene
            scene()->removeItem(item);
            delete item;
            return;
        } // if the enemy collides with a worker, the worker gets killed immediately
        else if(typeid(*item) == typeid(Worker)) {
            scene()->removeItem(item);
            game->decrementWorkersMaxCount();
            game->decrementWorkersAvaCount();
            delete item;
        }
    }

    const int STEP_SIZE = 1; //the velocity of the enemy

    double theta = rotation(); // degrees

    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);

}

// health functions
void Enemy::setHealth(int x)
{
    health = x;
}

void Enemy::decrementHealth(int x)
{
    health -= x;
    if(health <= 0) {
        // remove the enemy if its health goes below zero
        scene()->removeItem(this);
        delete this;
    }
}


void Enemy::incrementHealth(int x)
{
    health += x;
}

int Enemy::getHealth()
{
    return health;
}
