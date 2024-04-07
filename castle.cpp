#include "castle.h"
#include "game.h"

extern Game* game;

Castle::Castle() {
    QPixmap castleImg(":/images/img/castle.png");
    castleImg = castleImg.scaled(100, 100);
    setPixmap(castleImg);
}

/*
void setHealth(int);
    void decrementHealth(int);
    void incrementHealth(int);
    int getHealth();
*/

void Castle::setHealth(int x)
{
    health = x;
}

void Castle::decrementHealth(int x)
{
    health -= x;
}


void Castle::incrementHealth(int x)
{
    health += x;
}

int Castle::getHealth()
{
    return health;
}

