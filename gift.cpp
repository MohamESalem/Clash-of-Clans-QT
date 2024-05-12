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
        game->playSound(QUrl("qrc:/audio/audio/castle-s health improved 3.wav"));
        game->getCastle()->incrementCurrHealth(20);
    } else if(type == 1) {
        game->playSound(QUrl("qrc:/audio/audio/castle shield-s provided 6.wav"));
        game->shieldCastle();
    } else {
        game->playSound(QUrl("qrc:/audio/audio/Fire.m4a"));
        game->doubleBullets();
    }
}

