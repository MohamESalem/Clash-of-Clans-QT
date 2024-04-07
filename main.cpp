#include <QApplication>
#include "game.h"
#include "menu.h"

Game* game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //game
    game = new Game();
    //menu
    menu m;
    m.show();

    return a.exec();
}
