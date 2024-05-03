#include "castle.h"
#include "game.h"

extern Game* game;

// constructor
Castle::Castle(int x, int y) {
    QPixmap castleImg(":/images/img/castle.png");
    castleImg = castleImg.scaled(100, 100);
    setPixmap(castleImg);
    // initialize data mambers
    this->x = x;
    this->y = y;
    setPos(this->x, this->y);
    maxHealth = 100;
    currHealth = maxHealth;
    // initialize healthBar
    healthBar = new HealthBar(this->x, this->y, 100, maxHealth);
    healthBar->show();
    finished = false;

}

// health functions
void Castle::setCurrHealth(int x)
{
    currHealth = x;
}

void Castle::decrementCurrHealth(int x)
{
    currHealth -= x;
    // qDebug() << "Health = " << currHealth << '\n';
    healthBar->decrementCurrHealth(x);
    if(!finished && currHealth <= 0) {
        finished = true;
        game->mDelay(125);
        game->gameOver();
    }
}

void Castle::incrementCurrHealth(int x, QTimer*& moveTimer, QTimer*& healTimer)
{

    if(currHealth + x <= maxHealth)
        currHealth += x;
    if(isCurrHealthMax()) {
        healTimer->stop();
        moveTimer->start(250);
    }
}

bool Castle::isCurrHealthMax()
{
    return currHealth == maxHealth;
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

