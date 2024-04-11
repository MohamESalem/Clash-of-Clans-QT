#include "tent.h"

Tent::Tent(int x, int y)
{
    len = 75;
    this->x = x; this->y = y;
    setPixmap(QPixmap(":/images/img/tent.png").scaled(len, len));
    setPos(x, y);
    setZValue(4);
}

int Tent::getX() {return x;}
int Tent::getY() {return y;}

void Tent::setX(int x) {this->x = x;}
void Tent::setY(int y) {this->y = y;}
