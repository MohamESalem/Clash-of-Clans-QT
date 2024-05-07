#include "cannon.h"
#include "game.h"

extern Game* game;

Cannon::Cannon(int x, int y) {
    setPixmap(QPixmap(":/images/img/cannon2.png").scaled(80, 80));
    this->x = x;
    this->y = y;
    setPos(x, y);
    numBullets = 1;
    setTransformOriginPoint(40, 40);
}

// getters
int Cannon::getX() {return x;}
int Cannon::getY() {return y;}
int Cannon::getNumBullets() {return numBullets;}

// setters
void Cannon::setX(int x) {this->x = x;}
void Cannon::setY(int y) {this->y = y;}
void Cannon::setNumBullets(int b) {numBullets = b;}
