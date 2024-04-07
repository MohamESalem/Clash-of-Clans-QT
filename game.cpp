#include "game.h"
#include "fence.h"
#include "startmenu.h"

Game::Game() {
    // initialize variables
    blockUnit = 50;
    // initialize the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 800, 600);
    // create a view
    setFixedSize(800, 600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWindowTitle("Clash Of Clans");
    setWindowIcon(QIcon(":/images/img/icon.png"));
}

//.create a startMenu .add to scene

void Game::start() {
    // add the scene to the view
    setScene(scene);
    //drawe board
    drawBoard(":/board/boardFiles/board1.txt");
    // show the view
    show();
}

// getters
int Game::getBlockUnit() {return blockUnit;}
Castle* Game::getCastle() {return castle;}
Cannon* Game::getCannon() {return cannon;}

// public methods //! read file and write to array(boardData)
void Game::readBoardData(QString path) {
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    for(int i = 0; i < 12; i++) {
        for(int j = 0; j < 16; j++) {
            QString tmp;
            stream >> tmp;
            boardData[i][j] = tmp.toInt();
        }
    }
}

//
void Game::drawBoard(QString path) {
    readBoardData(path);
    bool isCastleDrawn = false;
    QPixmap grass(":/images/img/grass.png");
    grass = grass.scaled(blockUnit, blockUnit);
    for(int i = 0; i < 12; i++) {
        for(int j = 0; j < 16; j++) {
            // the x and y positions for the current iteration
            int x = j * blockUnit, y = i * blockUnit;

            // add the grass to the scene
            boardImages[i][j].setPixmap(grass);
            boardImages[i][j].setPos(x, y);
            scene->addItem(&boardImages[i][j]);

            // check the boardData
            if(boardData[i][j] == 3) {
                Fence* f = new Fence(x, y);
                scene->addItem(f);
                f->setZValue(1);
            } else if(boardData[i][j] == 1 && !isCastleDrawn) {
                castle = new Castle();
                castle->setPos(x, y);
                scene->addItem(castle);
                isCastleDrawn = true;
                castle->setZValue(2);
            } else if(boardData[i][j] == 2) {
                cannon = new Cannon();
                scene->addItem(cannon);
                // scene->removeItem(&boardImages[i][j]);
                cannon->setPos(x, y);
                cannon->setZValue(2);
            }

        }
    }
}
