#include "tent.h"

Tent::Tent(int x, int y)
{
    len = 75;
    this->x = x;
    this->y = y;
    row = (y + 20)/50;
    col = (x - 20)/50;
    setPixmap(QPixmap(":/images/img/tent.png").scaled(len, len));
    setPos(x, y);
    setZValue(3);
}

int Tent::getX() {return x;}
int Tent::getY() {return y;}
int Tent::getRow() {return row;}
int Tent::getCol() {return col;}

void Tent::setX(int x) {this->x = x;}
void Tent::setY(int y) {this->y = y;}
