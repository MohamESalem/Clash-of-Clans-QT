#include "cannon.h"
#include "game.h"

extern Game* game;

Cannon::Cannon(int x, int y) {
    setPixmap(QPixmap(":/images/img/cannon.png").scaled(60, 60));
    this->x = x;
    this->y = y;
    setPos(x, y);
    setTransformOriginPoint(30, 30);
}

// getters
int Cannon::getX() {return x;}
int Cannon::getY() {return y;}

// setters
void Cannon::setX(int x) {this->x = x;}
void Cannon::setY(int y) {this->y = y;}
