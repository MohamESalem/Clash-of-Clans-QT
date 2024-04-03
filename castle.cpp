#include "castle.h"
#include "game.h"

extern Game* game;

Castle::Castle() {
    QPixmap castleImg(":/images/img/castle.png");
    castleImg = castleImg.scaled(100, 100);
    setPixmap(castleImg);
}
