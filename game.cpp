#include <QLineF>
#include "game.h"
#include "fence.h"
#include "bullet.h"
#include "enemy.h"
#include <cstdlib>
#include <ctime>



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
    //design the timer label
    timerLabel = new QGraphicsTextItem();
    timerLabel->setPos(10, 10);
    timerLabel->setZValue(10);
    timerLabel->setDefaultTextColor(Qt::white);
    // Set the font size
    QFont font = timerLabel->font();
    font.setPointSize(18);
    timerLabel->setFont(font);
    scene->addItem(timerLabel);
    //update the timer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Game::updateTimer);
    duration = 1 * 60;

}

//.create a startMenu .add to scene

void Game::start() {
    // add the scene to the view
    setScene(scene);
    //drawe board
    drawBoard(":/board/boardFiles/board1.txt");
    //timer
    timer->start(1000);
    show();
}


void Game::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        Bullet* b = new Bullet();
        int offset = 25;
        int newX = cannon->getX() + offset, newY = cannon->getY() + offset;
        b->setPos(newX, newY); // set the position of the bullet to the center of the cannon

        QLineF ln(QPointF(newX, newY), event->pos());
        int angle = -1 * ln.angle();

        b->setRotation(angle);
        scene->addItem(b);
    }

}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    QLineF ln(QPointF(cannon->getX(), cannon->getY()), event->pos());
    int angle = -1 * ln.angle();
    // cannon->setRotation(angle - 30);
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
            } else if(boardData[i][j] == 1) {
                castle = new Castle();
                castle->setPos(x, y);
                scene->addItem(castle);
                castle->setZValue(2);
            } else if(boardData[i][j] == 2) {
                cannon = new Cannon(x, y);
                scene->addItem(cannon);
                cannon->setZValue(2);
            }

        }
    }
    int enemyNumber = 10;
    srand(time(0));
    while(enemyNumber) {
        int i = rand() % 16;
        int j = rand() % 12;
        int x = j * blockUnit, y = i * blockUnit;
        if(boardData[i][j]==0) {
            Enemy* enemy = new Enemy(x,y);
            QLineF ln(QPointF(8 * blockUnit, 7 * blockUnit), enemy->pos());
            int angle = -1 * ln.angle();

            scene->addItem(enemy);
            enemy->setZValue(1);
            enemy->move(angle);
            enemyNumber--;


        }

    }
}

void Game::updateTimer() {
    duration--;

    if (duration <= 0) {
        timer->stop();
    }

    int minutes = (duration % 3600) / 60;
    int seconds = duration % 60;

    // Format the time string
    QString timeString = QString("%1:%2").arg(minutes, 2, 10, QChar('0'))
                                         .arg(seconds, 2, 10, QChar('0'));
    timerLabel->setPlainText(timeString);
}
