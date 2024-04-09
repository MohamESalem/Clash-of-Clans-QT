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


void Enemy::moveRandomly()
{

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
