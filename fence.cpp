#include "fence.h"
#include "game.h"

extern Game* game;

Fence::Fence(int x, int y) {
    QPixmap fenceImg(":/images/img/fence.png");
    fenceImg = fenceImg.scaled(game->getBlockUnit(), game->getBlockUnit());
    setPixmap(fenceImg);
    setPos(x, y);
}

void Fence::setHealth(int x)
{
    health = x;
}

void Fence::decrementHealth(int x)
{
    health -= x;
}


void Fence::incrementHealth(int x)
{
    health += x;
}

int Fence::getHealth()
{
    return health;
}
