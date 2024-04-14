#include "worker.h"
#include "game.h"
#include "tent.h"

extern Game* game;

Worker::Worker() {
    int len = 56;
    setPixmap(QPixmap(":/images/img/worker.png").scaled(len, len));
    setTransformOriginPoint(len/2.0, len/2.0);
    int offset = 20;
    castle = game->getCastle();
    tent = game->getTent();
    setPos(tent->getX() - offset, tent->getY() + offset);
    healAbility = 10;
    setZValue(3);


    // set timers
    moveTimer = new QTimer(this);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    healTimer = new QTimer(this);
    connect(healTimer, &QTimer::timeout, [this](){
        if(castle->getCurrHealth() > 0)
            castle->incrementCurrHealth(this->healAbility, this->moveTimer,this->healTimer);
    });
    moveTimer->start(250);
}

int Worker::getHealAbility(){return healAbility;}
void Worker::setHealAbility(int x) {healAbility = x;}

void Worker::healCastle()
{
    healTimer->start(1000);
}

void Worker::move() {

    // set the destination (either to the castle or the tent)
    int detOffset = 45;
    int detX = castle->isCurrHealthMax() ? tent->getX() : castle->getX() + detOffset,
        detY = castle->isCurrHealthMax() ? tent->getY() : castle->getY() + detOffset;


    if(!castle->isCurrHealthMax()) {
        // check if the worker has reached the castle
        QList<QGraphicsItem *> collided_items = collidingItems();
        foreach(auto& item, collided_items) {
            if(typeid(*item) == typeid(Castle)) {
                moveTimer->stop();
                healCastle();
            }
        }
    }
    else {
        QList<QGraphicsItem *> collided_items = collidingItems();
        foreach(auto& item, collided_items) {
            if(typeid(*item) == typeid(Tent)) {
                moveTimer->stop();
                scene()->removeItem(this);
                game->decrementWorkersAvaCount();
                delete this;
                return;
            }
        }
    }

    // move to the destination
    const int STEP_SIZE = 5; // this represents the velocity of the worker
    QLineF ln(QPointF(x(), y()), QPointF(detX, detY));
    double angle = -1 * ln.angle();

    double theta = angle; // degrees

    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);

}
