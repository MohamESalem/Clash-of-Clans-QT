#include "castle.h"
#include "game.h"

extern Game* game;

// constructor
Castle::Castle(int x, int y) {
    QPixmap castleImg(":/images/img/castle.png");
    castleImg = castleImg.scaled(100, 100);
    setPixmap(castleImg);
    this->x = x;
    this->y = y;
    setPos(this->x, this->y);
    maxHealth = 100;
    currHealth = maxHealth;
}

// health functions
void Castle::setCurrHealth(int x)
{
    currHealth = x;
}

void Castle::decrementCurrHealth(int x)
{
    currHealth -= x;
    if(currHealth < 0) currHealth = 0;
    // show the game overwindow if currHealth == 0

}

void Castle::incrementCurrHealth(int x)
{
    currHealth += x;
    if(currHealth > maxHealth) currHealth = maxHealth;
}

int Castle::getCurrHealth()
{
    return currHealth;
}

// getters
int Castle::getX() {return x;}
int Castle::getY() {return y;}

// setters
void Castle::setX(int x) {this->x = x;}
void Castle::setY(int y) {this->y = y;}
