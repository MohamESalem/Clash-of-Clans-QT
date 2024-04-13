#include "enemy.h"
#include "game.h"
#include <QPixmap>
#include <QTimer>
#include <QTime>
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
    setZValue(3);
    castle = game->getCastle();
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveRandomly()));
    timer->start(50);
    health = 60;


}

void Enemy::moveRandomly()
{
    // set the destination (either to the castle or the tent)
    int detOffset = 45;
    int detX = castle->getX() + detOffset,
        detY =castle->getY() + detOffset;

    // move to the destination
    const int STEP_SIZE = 1; // this represents the velocity of the worker
    QLineF ln(QPointF(x(), y()), QPointF(detX, detY));
    double angle = -1 * ln.angle();

    double theta = angle; // degrees

    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);

    //will need to recheck the case when touch the fence (it'll need to stop for a while until it removed, so I'll implement decreasing health later)
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

        else if(typeid(*item) == typeid(Castle)) {
            game->getCastle()->decrementCurrHealth(10);
            setPos(x()-20*dx, y()-20*dy);
            if(game->getCastle()->getCurrHealth()<=0) {
                scene()->removeItem(item);
                delete item;

            }
            delay(1);

        }
    }




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

void Enemy::delay(int sec)
{
    QTime dieTime = QTime::currentTime().addSecs(sec);
    while(QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}
