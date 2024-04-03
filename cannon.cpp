#include "cannon.h"
#include "game.h"

extern Game* game;

Cannon::Cannon() {
    setPixmap(QPixmap(":/images/img/cannon.png").scaled(60, 60));
}
