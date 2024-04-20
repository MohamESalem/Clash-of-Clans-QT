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
    QTimer* timer = new QTimer(game);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveRandomly()));
    timer->start(50);
    health = 60;
    damage = 20;
}

void Enemy::moveRandomly()
{
    if(!contact) {
        // set the destination (either to the castle or the tent)

        int detOffset = 45;
        int detX = castle->getX() + detOffset,
            detY =castle->getY() + detOffset;

        // move to the destination
        const int STEP_SIZE = 3; // this represents the velocity of the worker
        QLineF ln(QPointF(x(), y()), QPointF(detX, detY));
        double angle = -1 * ln.angle();

        double theta = angle; // degrees

        double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
        double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));
        setPos(x()+dx, y()+dy);
    }

    QList<QGraphicsItem *> collided_items = collidingItems();
    foreach(auto& item, collided_items) {
        if(typeid(*item) == typeid(Fence)) {
            //Logic Explanation: when a contact happens, a pointer is created to the current
            // damaged fence, the health decreases, and the contact is changed to true to stop
            // the enemy from moving (because movement causes some errors)
            Fence *f = dynamic_cast<Fence*>(item);
            f->decrementHealth(damage);
            contact = true;
            game->mDelay(650);
            return;

        } // if the enemy collides with a worker, the worker gets killed immediately
        else if(typeid(*item) == typeid(Worker)) {
            Worker *w = dynamic_cast<Worker*>(item);
            if(w) {
                scene()->removeItem(item);
                w->getGroup()->changeIsAlive(w->getClanIndex());
                delete item;
            }
        }
        else if(typeid(*item) == typeid(Castle)) {
            game->getCastle()->decrementCurrHealth(damage);
            qDebug() << "Castle's health =  " << game->getCastle()->getCurrHealth() << '\n';
            if(game->getCastle() && game->getCastle()->getCurrHealth()<=0) {
                if(game->getCastle()) game->gameOver();
                // don't remove the castle; this may cause some bugs as many objects interact with the castle simultaneously
            }
            contact = true;
            game->mDelay(850);
            return;
        }

        contact = false;
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
