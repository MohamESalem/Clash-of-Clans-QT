#include "enemy.h"
#include "game.h"
#include <QPixmap>
#include <QTimer>
#include <QTime>
#include <qmath.h>
#include <QDebug>
#include <QGraphicsScene>
#include "worker.h"

extern Game* game;

Enemy::Enemy(int x, int y)
{
    // set the picture
    imgLen = 65;
    QPixmap enemyImg(":/images/img/enemy/enemy.png");
    enemyImg = enemyImg.scaled(imgLen, imgLen);
    setPixmap(enemyImg);
    // testing rotation
    setTransformOriginPoint(imgLen/2.0,imgLen/2.0);
    // setRotation(180);
    i = 0;
    setPos(x,y);
    setZValue(3);
    // set the postion
    castle = game->getCastle();
    health = 60;
    damage = 20;
    // fill the attackImgs QStringList
    attackImgs.append(":/images/img/enemy/enemy.png");
    attackImgs.append(":/images/img/enemy/1.png");
    attackImgs.append(":/images/img/enemy/2.png");
    attackImgs.append(":/images/img/enemy/3.png");
    attackImgs.append(":/images/img/enemy/4.png");
    // timers
    attackTimer = new QTimer(this);
    connect(attackTimer, &QTimer::timeout, [this]() {
        static int i = 0;
        if(!attackImgs.isEmpty()) setPixmap(QPixmap(attackImgs[i]).scaled(imgLen,imgLen));
        i = (i + 1) % attackImgs.size();
        // qDebug() << "Hi";
    });
    damageTimer = new QTimer(this);
    moveTimer = new QTimer(this);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(moveRandomly()));
    moveTimer->start(50);
}

Enemy::~Enemy() {attackImgs.clear();}

void Enemy::moveRandomly() {

    // if(!contact) {
    // attackTimer->stop();
    // setPixmap(QPixmap(attackImgs[0]).scaled(imgLen,imgLen));
        // set the destination (either to the castle or the tent)
        setPixmap(QPixmap(attackImgs[0]).scaled(imgLen,imgLen));
        attackTimer->stop();
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

    QList<QGraphicsItem *> collided_items = collidingItems();
    foreach(auto& item, collided_items) {
        if(typeid(*item) == typeid(Fence)) {
            Fence *f = dynamic_cast<Fence*>(item);
            if(f != NULL && f->getHealth() > 0)
                attackFence(f);
            return;

            // f->decrementHealth(damage);
            // contact = true;
            // mDelay(700);

        } // if the enemy collides with a worker, the worker gets killed immediately
        else if(typeid(*item) == typeid(Worker)) {
            Worker *w = dynamic_cast<Worker*>(item);
            if(w) {
                attackAnimate();
                w->getGroup()->changeIsAlive(w->getClanIndex());
                w->die();
                delete item;
                // qDebug() << "worked died!\n";
            }
        }
        else if(typeid(*item) == typeid(Castle)) {
            // game->getCastle()->decrementCurrHealth(damage);
            attackCastle();
            // if(game->getCastle() && game->getCastle()->getCurrHealth()<=0) {
            //     if(game->getCastle()) game->gameOver();
            // }
            // contact = true;
            // mDelay(850);
            return;
        }

        // contact = false;
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

void Enemy::attackAnimate() {
    for(int i = 0; i < attackImgs.size(); i++) {
        if(!game->getScene()->items().isEmpty()) setPixmap(QPixmap(attackImgs[i]).scaled(imgLen,imgLen));
        if(i != attackImgs.size() - 1) mDelay(100);
    }
    if(!game->getScene()->items().isEmpty()) setPixmap(QPixmap(attackImgs[0]).scaled(imgLen,imgLen));
}

int Enemy::getHealth()
{
    return health;
}


void Enemy::mDelay(int mSec)
{
    QTime dieTime = QTime::currentTime().addMSecs(mSec);
    while(QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void Enemy::attackFence(Fence *&f) {
    if(f != NULL && f->getHealth() > 0) {
        disconnect(damageTimer, &QTimer::timeout, nullptr, nullptr);
        connect(damageTimer, &QTimer::timeout, [this,f]() {
            f->decrementHealth(this->damage, this->moveTimer, this->damageTimer);
        });
        moveTimer->stop();
        damageTimer->start(800);
        attackTimer->start(160);
    }
}

void Enemy::attackCastle() {
    disconnect(damageTimer, &QTimer::timeout, nullptr, nullptr);
    connect(damageTimer, &QTimer::timeout, [this]() {
        game->getCastle()->decrementCurrHealth(this->damage);
    });
    moveTimer->stop();
    damageTimer->start(800);
    attackTimer->start(160);
}
