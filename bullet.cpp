#include "bullet.h"
#include "enemy.h"
#include "gift.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>
#include <QDebug>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "game.h"

extern Game* game;

Bullet::Bullet() {
    // initialize the bullet picture and dimensions
    int len = 30;
    if(game->getMap() != 3) {
        setPixmap(QPixmap(":/images/img/bullet.png").scaled(len, len));
    } else {
        setPixmap(QPixmap(":/images/img/bullet2.png").scaled(len, len));
    }
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
    damage = 20;
    setZValue(5);
    //play sound
    game->playSound(QUrl("qrc:/audio/audio/bullet.wav"));
}

int Bullet::getDamage() {return damage;}
void Bullet::setDamage(int x) {damage = x;}

void Bullet::move() {
    // handle if the bullet collides with an enemy

    QList<QGraphicsItem *> collided_items = collidingItems();
    foreach(auto& item, collided_items) {
        if(item && typeid(*item) == typeid(Enemy)) {
            Enemy* e = dynamic_cast<Enemy*> (item);
            e->decrementHealth(damage);
            // remove the bullet from the scene
            scene()->removeItem(this);
            // release the memory from the heap
            delete this;
            return;
        } else if(item && typeid(*item) == typeid(Gift)) {
            Gift* g = dynamic_cast<Gift*> (item);
            if(g != NULL) {
                g->utilize();
                game->getScene()->removeItem(g);
                delete g;
                game->getScene()->removeItem(this);
                delete this;
                return;
            }
        }
    }

    // handle the bullet movement

    const int STEP_SIZE = 20; // this represents the velocity of the bullet

    double theta = rotation(); // degrees

    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);

    // handle the case when the bullet goes out of the view
    if(y() < 0  || y() > scene()->height() || x() < 0 || x() > scene()->width()) {
        scene()->removeItem(this);
        delete this;
    }
}

