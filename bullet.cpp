#include "bullet.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>
#include <QDebug>
#include <QGraphicsScene>

Bullet::Bullet() {
    // initialize the bullet picture and dimensions
    int len = 30;
    setPixmap(QPixmap(":/images/img/bullet.png").scaled(len, len));
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

void Bullet::move() {
    // handle if the bullet collides with an enemy

    // *** UNCOMMENT this part when the Enemy class is created ***

    // QList<QGraphicsItem *> collided_items = collidingItems();
    // foreach(auto& item, collided_items) {
    //     if(typeid(*item) == typeid(Enemy)) {
    //         // remove the item from the scene
    //         scene()->removeItem(this);
    //         // release the memory from the heap
    //         delete this;
    //         return;
    //     }
    // }

    // handle the bullet movement

    const int STEP_SIZE = 20; // this represents the velocity of the bullet

    double theta = rotation(); // degrees

    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);

    // handle if the bullet goes out of the view
    if(y() < 0  || y() > scene()->height() || x() < 0 || x() > scene()->width()) {
        scene()->removeItem(this);
        delete this;
    }

}
