#include "enemy.h"
#include "game.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>
#include <QDebug>
#include <QGraphicsScene>
#include "fence.h"

extern Game* game;

Enemy::Enemy(int x, int y)
{
    QPixmap enemyImg(":/images/img/enemy.png");
    enemyImg = enemyImg.scaled(game->getBlockUnit(), game->getBlockUnit());
    setPixmap(enemyImg);
    setPos(x,y);
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveRandomly()));
    timer->start(50);

}



void Enemy::moveRandomly()
{
    QList<QGraphicsItem *> collided_items = collidingItems();
    foreach(auto& item, collided_items) {
        if(typeid(*item) == typeid(Fence)) {
            // remove the item from the scene
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    const int STEP_SIZE = 1; //the velocity of the enemy

    double theta = rotation(); // degrees

    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);

}


void Enemy::setHealth(int x)
{
    health = x;
}

void Enemy::decrementHealth(int x)
{
    health -= x;
}


void Enemy::incrementHealth(int x)
{
    health += x;
}

int Enemy::getHealth()
{
    return health;
}
