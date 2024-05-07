#include "gift.h"
#include "game.h"

extern Game* game;

Gift::Gift(int x, int y, int t) {
    int imgLen = 43;
    type = t;
    setPos(x, y);
    setZValue(2);
    QPixmap img;
    switch(type) {
        case 0:
            img = QPixmap(":/images/img/gifts/green.png").scaled(imgLen, imgLen);
            break;
        case 1:
            img = QPixmap(":/images/img/gifts/blue.png").scaled(imgLen, imgLen);
            break;
        default:
            img = QPixmap(":/images/img/gifts/purple.png").scaled(imgLen, imgLen);
    }
    setPixmap(img);
}

void Gift::utilize() {
    if(type == 0) {
        game->getCastle()->incrementCurrHealth(20);
    } else if(type == 1) {
        game->shieldCastle();
    } else {
        game->doubleBullets();
    }
}

