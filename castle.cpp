#include "castle.h"
#include "game.h"
#include <QMediaPlayer>
#include <QAudioOutput>

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
    isShielded = false;
    finished = false;

}

// health functions
void Castle::setCurrHealth(int x)
{
    currHealth = x;
    healthBar->setCurrHealth(x);
}

void Castle::decrementCurrHealth(int x)
{
    if(!isShielded) {
    game->playSound(QUrl("qrc:/audio/audio/enemydamagefenceandcastle.wav"));

        currHealth -= x;
        // qDebug() << "Health = " << currHealth << '\n';
        healthBar->decrementCurrHealth(x);
        if(!finished && currHealth <= 0) {
            finished = true;
            game->mDelay(125);
            game->gameOver();
        }
    }
}

void Castle::incrementCurrHealth(int x)
{

    if(currHealth + x <= maxHealth) {
        currHealth += x;
        healthBar->incrementCurrHealth(x);
    }
}

bool Castle::isCurrHealthMax()
{
    return currHealth == maxHealth;
}

void Castle::shield()
{
    isShielded = true;
    healthBar->provideShield();
}

void Castle::removeShield()
{
    isShielded = false;
    healthBar->removeShield();
}

int Castle::getCurrHealth()
{
    return currHealth;
}

// getters
int Castle::getX() {return x;}
int Castle::getY() {return y;}
bool Castle::getIsShielded() {return isShielded;}

// setters
void Castle::setX(int x) {this->x = x;}
void Castle::setY(int y) {this->y = y;}
void Castle::setIsShielded(bool b) {isShielded = b;}

