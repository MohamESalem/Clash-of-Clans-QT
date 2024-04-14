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

    // initialize variables
    blockUnit = 50;
    workersMaxCount = 3;
    workersAvaCount = 0;

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
    // create a view


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
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    duration = 1 * 60;

    // start the timer
    timer->start(1000);

    show();
    delay(2);
    gameOver();
    //spawning enemies
    // spawnEnemies();
}

void Game::gameOver()
{
    gameover *o = new gameover();
    timer->stop();
    close();
    o->show();
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
    // cannon->setRotation(angle - 30);
}


// getters
int Game::getBlockUnit() {return blockUnit;}
Castle* Game::getCastle() {return castle;}
Cannon* Game::getCannon() {return cannon;}
Tent* Game::getTent() {return tent;}

void Game::makeWorkers()
{
    qDebug() << "Castle health is now " << castle->getCurrHealth() << '\n';
    int last = workersMaxCount - workersAvaCount;
    for(int i = 0; i < last; i++) {
        Worker* w = new Worker();
        scene->addItem(w);
        incrementWorkersAvaCount();
        if(i != last - 1) delay(2);
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
    int enemyNumber = 5;
    srand(time(0));
    while(enemyNumber) {
        int i = rand() % 4;
        if(i==0) {

            Enemy* enemy = new Enemy(0,0);
            scene->addItem(enemy);
        }

        else if(i==1) {
            Enemy* enemy = new Enemy(800,600);
            scene->addItem(enemy);
        }

        else if(i==2) {
            Enemy* enemy = new Enemy(800,0);
            scene->addItem(enemy);
        }

        else {
            Enemy* enemy = new Enemy(0,600);
            scene->addItem(enemy);
        }

        enemyNumber--;
        delay(2);
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
        timer->stop();
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
