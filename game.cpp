#include <QLineF>
#include "game.h"
#include "fence.h"
#include "bullet.h"
#include "worker.h"
#include "gameover.h"
#include <QTime>
#include "enemy.h"
#include <cstdlib>
#include <ctime>

Game::Game() {
    // initialize the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 800, 600);
    // initialize the view's properties
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
    // initialize variables
    blockUnit = 50;
    workersMaxCount = 5;
    workersAvaCount = 0;
    duration = 1 * 60;
    underExec = false;

    //draw board
    drawBoard(":/board/boardFiles/board1.txt");

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
    gameTimer = new QTimer(this);
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    enemyTimer = new QTimer(this);
    connect(enemyTimer, SIGNAL(timeout()), this, SLOT(spawnEnemies()));

    // start the timers
    gameTimer->start(1000);
    enemyTimer->start(2000);

    show();
    // testing gameOver() window
    // delay(4);
    // gameOver();
}

void Game::gameOver()
{
    gameover *o = new gameover();
    // stop timers
    gameTimer->stop();
    enemyTimer->stop();
    // close and show the correct windows
    close();
    o->show();
    // clear the scene
    foreach(QGraphicsItem *item, scene->items()) { // not working
        scene->removeItem(item);
        delete item;
    }
    scene->clear();
}


void Game::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        Bullet* b = new Bullet();
        int offset = 25;
        int newX = cannon->getX() + offset, newY = cannon->getY() + offset;
        b->setPos(newX, newY); // set the position of the bullet to the center of the cannon

        QLineF ln(QPointF(newX, newY), event->pos());
        double angle = -1 * ln.angle();

        b->setRotation(angle);
        scene->addItem(b);
    }

}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    QLineF ln(QPointF(cannon->getX(), cannon->getY()), event->pos());
    double angle = -1 * ln.angle();
    int offset = 30;
    cannon->setRotation(angle - offset);
}


// getters
int Game::getBlockUnit() {return blockUnit;}
Castle* Game::getCastle() {return castle;}
Cannon* Game::getCannon() {return cannon;}
Tent* Game::getTent() {return tent;}

void Game::makeWorkers()
{
    if(castle && !underExec) {
        underExec = true;
        int last = workersMaxCount - workersAvaCount;
        for(int i = 0; i < last; i++) {
            if(castle) {
                incrementWorkersAvaCount();
                Worker* w = new Worker();
                scene->addItem(w);
                if(i != last - 1) delay(2);
            } else {
                break;
            }
        }
        underExec = false;
    }
}

void Game::decrementWorkersMaxCount()
{
    if(workersMaxCount > 0) workersMaxCount--;
}

void Game::incrementWorkersAvaCount()
{
    if(workersAvaCount < workersMaxCount) workersAvaCount++;
}

void Game::decrementWorkersAvaCount()
{
    if(workersAvaCount > 0) workersAvaCount--;
}

void Game::spawnEnemies()
{
    srand(time(0));
    int i = rand() % 4;
    int randX = rand() % 801, randY = rand() % 601;
    if(i == 0) {
        // spawn at the top
        Enemy* enemy = new Enemy(randX, 0);
        scene->addItem(enemy);
    }
    else if(i == 1) {
        // spawn at the bottom
        Enemy* enemy = new Enemy(randX, 600);
        scene->addItem(enemy);
    }
    else if(i == 2) {
        // spawn on the left
        Enemy* enemy = new Enemy(800, randY);
        scene->addItem(enemy);
    }
    else {
        // spawn at the right
        Enemy* enemy = new Enemy(800, randY);
        scene->addItem(enemy);
    }
}

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
            boardImages[i][j] = new QGraphicsPixmapItem(grass);
            boardImages[i][j]->setPos(x, y);
            scene->addItem(boardImages[i][j]);

            // check the boardData

            if(boardData[i][j] == 3) {
                Fence* f = new Fence(x, y);
                scene->addItem(f);
                f->setZValue(1);
            } else if(boardData[i][j] == 1) {
                castle = new Castle(x, y);
                scene->addItem(castle);
                castle->setZValue(2);
            } else if(boardData[i][j] == 2) {
                cannon = new Cannon(x, y);
                scene->addItem(cannon);
                cannon->setZValue(3);
            } else if(boardData[i][j] == 4) {
                int offset = 20;
                tent = new Tent(x + offset, y - offset);
                scene->addItem(tent);
            }

        }
    }


}

void Game::updateTimer() {
    duration--;

    if (duration <= 0) {
        gameTimer->stop();
        // show the winning window

    }

    int minutes = (duration % 3600) / 60;
    int seconds = duration % 60;

    // Format the time string
    QString timeString = QString("%1:%2").arg(minutes, 2, 10, QChar('0'))
                                         .arg(seconds, 2, 10, QChar('0'));
    timerLabel->setPlainText(timeString);

}

void Game::delay(int sec)
{
    QTime dieTime = QTime::currentTime().addSecs(sec);
    while(QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}
