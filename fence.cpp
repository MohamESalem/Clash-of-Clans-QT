#include "fence.h"
#include "game.h"

extern Game* game;

Fence::Fence(int x, int y) {
    QPixmap fenceImg(":/images/img/fence.png");
    fenceImg = fenceImg.scaled(game->getBlockUnit(), game->getBlockUnit());
    setPixmap(fenceImg);
    setPos(x, y);
}
