#include <QApplication>
#include "game.h"
#include "menu.h"

Game* game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();
    menu m;
    m.show();

    return a.exec();
}
