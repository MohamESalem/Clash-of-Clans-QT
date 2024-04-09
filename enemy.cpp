#include "enemy.h"
#include "game.h"

extern Game* game;

Enemy::Enemy(int x, int y)
{
    QPixmap enemyImg(":/images/img/enemy.png");
    enemyImg = enemyImg.scaled(game->getBlockUnit(), game->getBlockUnit());
    setPixmap(enemyImg);
    setPos(x,y);

}

void Enemy::move(int angle) {
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveRandomly(angle)));
    timer->start(50);
}


void Enemy::moveRandomly(int angle)
{
    const int STEP_SIZE = 20; // this represents the velocity of the bullet

    double dy = STEP_SIZE * qSin(qDegreesToRadians(angle));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(angle));

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
