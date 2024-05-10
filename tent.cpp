#include "tent.h"
#include "game.h"

extern Game* game;

Tent::Tent(int x, int y)
{
    len = 75;
    this->x = x;
    this->y = y;
    row = (y + 20)/50;
    col = (x - 20)/50;
    if(game->getMap()==1) {
        setPixmap(QPixmap(":/images/img/tent.png").scaled(len, len));
    }

    else if (game->getMap()==2) {
        setPixmap(QPixmap(":/images/img/tent2.webp").scaled(75, 95));
    }

    else if (game->getMap()==3) {
        setPixmap(QPixmap(":/images/img/tent3.png").scaled(75, 95));
    }

    setPos(x, y);
    setZValue(3);
}

int Tent::getX() {return x;}
int Tent::getY() {return y;}
int Tent::getRow() {return row;}
int Tent::getCol() {return col;}

void Tent::setX(int x) {this->x = x;}
void Tent::setY(int y) {this->y = y;}
