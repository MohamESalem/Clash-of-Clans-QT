#include <QLineF>
#include "game.h"
#include "fence.h"
#include "bullet.h"
#include "gameover.h"
#include <QTime>
#include "enemy.h"
#include "winning.h"
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
    testFence = test2 = NULL;
}

//.create a startMenu .add to scene

void Game::start() {

    // add the scene to the view
    setScene(scene);
    // initialize variables
    blockUnit = 50;
    workersMaxCount = 5;
    workersAvaCount = 0;
    duration = 1 * 2;
    underExec = false;
    tent1 = tent2 = NULL;

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
    // spawnEnemies();
    enemyTimer->start(4000);

    show();

    // // stops group 2 for testing
    // group2->isAllClanDead = true;
    // group2->changeAvailability(false);

    // // testing WorkersClan
    // delay(3);
    // if(test2) {
    //     qDebug() << "Begin!\n";
    //     test2->decrementHealth(30);
    // }
    // delay(3);
    // if(testFence) {
    //     qDebug() << "New Test!\n";
    //     testFence->decrementHealth(10);
    //     qDebug() << "Test2 health = " << testFence->getHealth() << '\n';
    // }
    // delay(1);
    // if(test3) {
    //     qDebug() << "Hopefully, last test!\n";
    //     test3->decrementHealth(40);
    // }

    // // testing gameOver() window
    // delay(4);
    // gameOver();

}

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
                if(i == 5 && j == 3) {
                    testFence = f;
                } else if(i == 7 && j == 12) {
                    test2 = f;
                } else if(i == 3 && j == 8) {
                    test3 = f;
                }
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
                int tentX = x + offset, tentY = y - offset;
                if(tent1 == NULL) {
                    tent1 = new Tent(tentX, tentY);
                    group1 = new WorkersClan(2, tent1);
                    scene->addItem(tent1);
                } else {
                    tent2 = new Tent(tentX, tentY);
                    group2 = new WorkersClan(2, tent2);
                    scene->addItem(tent2);
                }
            }

        }
    }

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
        int offset = 40;
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
    // cannon->setRotation(angle - offset);
}


// getters
int Game::getBlockUnit() {return blockUnit;}
Castle* Game::getCastle() {return castle;}
Cannon* Game::getCannon() {return cannon;}
QGraphicsScene *Game::getScene() {return scene;}


// WorkersClan functions

int Game::getAvailableGroup(int x, int y)
{
    qDebug() << "group1's ava = " << group1->getAvailability() << ", group's 2 ava = " << group2->getAvailability() << '\n';
    if(group1->getAvailability() && group2->getAvailability()) {
        // qDebug() << "In your function, sir!\n";
        double dist1 = pow(group1->getTent()->getX() - x, 2) + pow(group1->getTent()->getY() - y, 2);
        double dist2 = pow(group2->getTent()->getX() - x, 2) + pow(group2->getTent()->getY() - y, 2);
        if(dist1 <= dist2)
            return 1;
        // the closer moves to the damaged fence
        else
            return 2;
    }
    else if(group1->getAvailability() && !group2->getAvailability()) {
        return 1; // group 1 should move
    }
    else if(group2->getAvailability() && !group1->getAvailability()) {
        return 2; // group 2 should move
    }
    else if(!group1->getIsAllClanDead() || !group2->getIsAllClanDead())
        return 0; // if one of the groups is not dead but all are busy
    else
        return -1; // the two groups are dead
}

WorkersClan *Game::getGroup1() {return group1;}
WorkersClan *Game::getGroup2() {return group2;}

// enemies functions

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


void Game::updateTimer() {
    duration--;

    if (duration <= 0) {
        // stop timers
        gameTimer->stop();
        enemyTimer->stop();
        // show the winning window
        close();
        winning *w = new winning;
        w->show();
        // clear the scene
        foreach(QGraphicsItem *item, scene->items()) { // not working
            scene->removeItem(item);
            delete item;
        }
        scene->clear();

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

void Game::mDelay(int mSec)
{
    QTime dieTime = QTime::currentTime().addMSecs(mSec);
    while(QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}
