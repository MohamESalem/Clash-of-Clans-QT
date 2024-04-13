#include <QApplication>
#include "game.h"
#include "menu.h"
#include "gameover.h"


Game* game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //gameN
    game = new Game();
    //menu
    // gameover o;
    // o.show();
    menu m;
    m.show();

    return a.exec();
}
