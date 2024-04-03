#include "game.h"

Game::Game() {
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 800, 600);
    setFixedSize(800, 600);
    // create a view
    setFixedSize(800, 600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWindowTitle("Clash Of Clans");
}

void Game::start() {
    // add the scene to the view
    setScene(scene);

    // show the view
    show();
}
