#include "worker.h"
#include "game.h"

extern Game* game;

Worker::Worker(WorkersClan* g, int index) {
    // set the workers' appearance
    int len = 56;
    setPixmap(QPixmap(":/images/img/worker.png").scaled(len, len));
    setTransformOriginPoint(len/2.0, len/2.0);

    // set the parameters & privat attributes
    group = g;
    clanIndex = index;
    healAbility = 10;

    // set the position and ZValue
    int offset = 20;
    setPos(group->getTent()->getX() - offset, group->getTent()->getY() + offset);
    setZValue(3);


    // set timers
    moveTimer = new QTimer(this);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    returnTimer = new QTimer(this);
    connect(returnTimer, SIGNAL(timeout()), this, SLOT(returnBack()));
    healTimer = new QTimer(this);

    // start the moveTimer
    moveTimer->start(250);
}

int Worker::getHealAbility(){return healAbility;}
void Worker::setHealAbility(int x) {healAbility = x;}

WorkersClan* Worker::getGroup() {return group;}
int Worker::getClanIndex() {return clanIndex;}

void Worker::healFence(Fence*f)
{
    if(!group->getAvailability()) {
        connect(healTimer, &QTimer::timeout, [this, f](){
            f->incrementHealth(this->healAbility, this->returnTimer, this->healTimer);
        });
        healTimer->start(1000);
    } else {
        returnTimer->start(250);
    }
}

void Worker::move() {

    if(group->getAvailability()) {
        // the fence was destroyed
        moveTimer->stop();
        returnTimer->start(250);
        return;
    } else {
        // the workers are under mission
        QList<QGraphicsItem *> collided_items = collidingItems();
        foreach(auto& item, collided_items) {
            if(typeid(*item) == typeid(Fence)) {

                Fence* f = dynamic_cast<Fence*>(item);
                if(f != NULL && f->getHealth() != f->getMaxHealth()) {
                        moveTimer->stop();
                        healFence(f);
                        return;
                }

            }
        }
    }

    // // move to the destination
    const int STEP_SIZE = 20; // this represents the velocity of the worker
    QLineF ln(QPointF(x(), y()), QPointF(group->getDetX(), group->getDetY()));
    double angle = -1 * ln.angle();

    double theta = angle; // degrees

    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);

}


void Worker::returnBack() {

    if(!group->getAvailability()) {
        returnTimer->stop();
        moveTimer->start(250);
        return;
    }

    int tentX = group->getTent()->getX(),
        tentY = group->getTent()->getY();

    QList<QGraphicsItem *> collided_items = collidingItems();
    foreach(auto& item, collided_items) {
        if(typeid(*item) == typeid(Tent) && dynamic_cast<Tent*>(item) == group->getTent()) {
            returnTimer->stop();
            this->group->changeWorkerPointerToNULL(clanIndex);
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    const int STEP_SIZE = 20; // this rep resents the velocity of the worker
    QLineF ln(QPointF(x(), y()), QPointF(tentX, tentY));

    double angle = -1 * ln.angle();

    double theta = angle; // degrees

    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);
}
