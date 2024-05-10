#include <QLineF>
#include "game.h"
#include "fence.h"
#include "bullet.h"
#include "gameover.h"
#include <QTime>
#include "enemy.h"
#include "winning.h"
#include "gift.h"
#include <cstdlib>
#include <ctime>
#include <QMediaPlayer>
#include <QAudioOutput>

Game::Game() {
    // initialize the scene
    scene = new QGraphicsScene();
    graph = new Graph();
    scene->setSceneRect(0, 0, 800, 600);
    // initialize the view's properties
    setFixedSize(800, 600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWindowTitle("Clash Of Clans");
    setWindowIcon(QIcon(":/images/img/icon.png"));
    testFence = test2 = NULL;
    startEnemy = {8000, 6000, 4000, 2000, 1000};
    startGift = {10 * 1000, 10 * 1000, 20 * 1000, 20 * 1000, 20 * 1000};
    castleHealth = 100;
    bonusDefaultDuration = 10 + 1;
    volume = 0.5;
    isVolSet = false;
    map = 1;
}

// graph-related functions
void Game::makeGraph()
{

    for(int i = 0; i < 12; i++) {
        for(int j = 0; j < 16; j++) {

            int weight = 1;
            if(boardData[i][j] == 3) {
                weight = 3;
            }
            else if(boardData[i][j] == 2 || boardData[i][j] == 4) {
                weight = 20;
            }
            Node* node = graph->makeNode(i,j,weight);
            graph->addNode(node);
        }
    }

    for(int i = 0; i < 12; i++) {
        for(int j = 0; j < 16; j++) {
            if(i!=11) {
                graph->addEdge(graph->findNode(i,j), graph->findNode(i+1,j));
            }

            if(i!=0) {
                graph->addEdge(graph->findNode(i,j), graph->findNode(i-1,j));
            }

            if(j!=0) {
                graph->addEdge(graph->findNode(i,j), graph->findNode(i,j-1));
            }

            if(j!=15) {
                graph->addEdge(graph->findNode(i,j), graph->findNode(i,j+1));
            }

            if(i!=0 && j!=0) {
                graph->addEdge(graph->findNode(i,j), graph->findNode(i-1,j-1));
            }

            if(i!=11 && j!=0) {
                graph->addEdge(graph->findNode(i,j), graph->findNode(i+1,j-1));
            }

            if(i!=11 && j!=0) {
                graph->addEdge(graph->findNode(i,j), graph->findNode(i+1,j-1));
            }

            if(i!=11 && j!=15) {
                graph->addEdge(graph->findNode(i,j), graph->findNode(i+1,j+1));
            }

            if(i!=0 && j!=15) {
                graph->addEdge(graph->findNode(i,j), graph->findNode(i-1,j+1));
            }


        }
    }

}

void Game::updateEnemyPath()
{
    // qDebug() << "Called\n";
    foreach (auto& item, enemies) {
        if (item != NULL) {
            item->updatePath();
        }
    }
}

void Game::shieldCastle()
{
    castle->shield();
    scene->addItem(bonusTimerLabel);
    bonusTimer->start(1000);
}

void Game::doubleBullets()
{
    isBulletBonus = true;
    scene->addItem(bonusTimerLabel);
    bonusTimer->start(1000);
}

void Game::updateBonusTimer()
{
    bonusDuration--;

    if (bonusDuration <= 0) {
        bonusDuration = bonusDefaultDuration;
        if(isBulletBonus) isBulletBonus = false;
        if(castle->getIsShielded()) castle->removeShield();
        bonusTimer->stop();
        scene->removeItem(bonusTimerLabel);
        return;
    }

    int minutes = (bonusDuration % 3600) / 60;
    int seconds = bonusDuration % 60;

    // Format the time string
    QString timeString = QString("%1:%2").arg(minutes, 2, 10, QChar('0'))
                             .arg(seconds, 2, 10, QChar('0'));
    bonusTimerLabel->setPlainText(timeString);
}

void Game::start(int level) {

    this->level = level;
    if(this->level == 0) castleHealth = 100;
    // add the scene to the view
    setScene(scene);
    // initialize variables
    blockUnit = 50;
    workersMaxCount = 5;
    workersAvaCount = 0;
    duration = 1 * 60;
    bonusDuration = bonusDefaultDuration;
    isBulletBonus = false;
    tent1 = tent2 = NULL;
    enemies.clear();
    damagedFence.clear();

    //draw board
    drawBoard(":/board/boardFiles/board1.txt");
    // graph->addNode(graph->makeNode(1,2,5));
    makeGraph();
    // int x = castle->getX();
    // int y = castle->getY();
    // graph->editStrength(3,5,1);
    // std::vector<Node*> path = graph->aStarAlgo(graph->findNode(0,0),graph->findNode(6,7));
    // for (size_t i = 0; i < path.size(); ++i) {
    //     qDebug() << path[i]->getX() << " " << path[i]->getY() << " ";
    // }


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

    // design the bonus timer label
    bonusTimerLabel = new QGraphicsTextItem();
    bonusTimerLabel->setPos(10, 10 + 25);
    bonusTimerLabel->setZValue(10);
    bonusTimerLabel->setDefaultTextColor(Qt::yellow);
    QFont bonusFont = bonusTimerLabel->font();
    bonusFont.setPointSize(18);
    bonusTimerLabel->setFont(bonusFont);

    //update the timer
    gameTimer = new QTimer(this);
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    enemyTimer = new QTimer(this);
    connect(enemyTimer, SIGNAL(timeout()), this, SLOT(spawnEnemies()));
    giftTimer = new QTimer(this);
    connect(giftTimer, SIGNAL(timeout()), this, SLOT(randGifts()));
    bonusTimer = new QTimer(this);
    connect(bonusTimer, SIGNAL(timeout()), this, SLOT(updateBonusTimer()));

    // start the timers
    gameTimer->start(1000);

    // spawnEnemies();

    show();
    // castle->decrementCurrHealth(40);

    delay(1);
    spawnEnemies();
    enemyTimer->start(startEnemy[level]);
    giftTimer->start(startGift[level]);
    // randGifts();

    // delay(2);
    // testFence->decrementHealth(80);
    // spawnEnemies();


    // stops groups 1 and 2 for testing
    // group1->isAllClanDead = true;
    // group1->changeAvailability(false);
    // group2->isAllClanDead = true;
    // group2->changeAvailability(false);

    // // testing WorkersClan
    // delay(1);
    // if(test2) {
    //     // qDebug() << "Begin!\n";
    //     test2->decrementHealth(40);
    //     // delay(1);
    //     // test2->decrementHealth(30);
    // }
    // delay(1);
    // if(testFence) {
        // qDebug() << "New Test!\n";
        // testFence->decrementHealth(15);
        // qDebug() << "Test2 health = " << testFence->getHealth() << '\n';
    // }
    // // // delay(1);
    // if(test3) {
    //     // qDebug() << "Hopefully, last test!\n";
    //     test3->decrementHealth(40);
    // }

    // test the health bar of the castle
    // delay(3);
    // castle->decrementCurrHealth(10);
    // delay(3);
    // castle->decrementCurrHealth(30);
    // delay(2);
    // castle->decrementCurrHealth(50);
    // delay(2);
    // castle->decrementCurrHealth(10);

    // // testing gameOver() and showWinningWdn()
    // delay(10);
    // gameOver();
    // showWinningWdn();

}

void Game::startNewLevel()
{
    // stop timers
    gameTimer->stop();
    enemyTimer->stop();
    giftTimer->stop();
    // close and show the correct windows
    castleHealth = castle->getCurrHealth();
    close();
    foreach(QGraphicsItem *item, scene->items()) { // not working
        scene->removeItem(item);
        delete item;
    }
    scene->clear();
    start(level + 1);
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
    // setMap(1);
    QPixmap ground;
    QPixmap ground2;
    if(getMap()==1) {
       ground = QPixmap(":/images/img/grass.png");
       ground2 = QPixmap(":/images/img/grass.png");
    }

    else if(getMap()==2) {
        ground = QPixmap(":/images/img/stone.png");
        ground2 = QPixmap(":/images/img/stone2.jpg");
    }

    else if(getMap()==3) {
        ground = QPixmap(":/images/img/ice.jpg");
        ground2 = QPixmap(":/images/img/ice2.jpg");
    }

    ground = ground.scaled(blockUnit, blockUnit);
    ground2 = ground2.scaled(blockUnit, blockUnit);

    for(int i = 0; i < 12; i++) {
        for(int j = 0; j < 16; j++) {
            // the x and y positions for the current iteration
            int x = j * blockUnit, y = i * blockUnit;

            // add the ground to the scene
            int k = rand() % 2;
            if(k==1) {
                boardImages[i][j] = new QGraphicsPixmapItem(ground);
            }

            else {
                // if(getMap()!=1) {
                    boardImages[i][j] = new QGraphicsPixmapItem(ground2);
                // }

                // else {
                    // boardImages[i][j] = new QGraphicsPixmapItem(ground);
                // }

            }

            boardImages[i][j]->setPos(x, y);
            scene->addItem(boardImages[i][j]);

            // check the boardData

            if(boardData[i][j] == 3) {
                Fence* f = new Fence(x, y);
                scene->addItem(f);
                f->setZValue(1);
                if(i == 8 && j == 6) {
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
                castle->setCurrHealth(castleHealth);
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
    giftTimer->stop();
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

void Game::showWinningWdn()
{
    winning *w = new winning();
    // stop the timers
    gameTimer->stop();
    enemyTimer->stop();
    giftTimer->stop();
    // close and show the winning window
    close();
    w->show();
    // clear the scene
    foreach(QGraphicsItem *item, scene->items()) {
        scene->removeItem(item);
        delete item;
    }
    scene->clear();
}


void Game::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        int last = 1 + isBulletBonus;
        for(int i = 0; i < last; i++) {
            Bullet* b = new Bullet();
            int offset = 40;
            int newX = cannon->getX() + offset, newY = cannon->getY() + offset;
            b->setPos(newX, newY); // set the position of the bullet to the center of the cannon

            QLineF ln(QPointF(newX, newY), event->pos());
            double angle = -1 * ln.angle();

            b->setRotation(angle);
            scene->addItem(b);
            if(i != last - 1) mDelay(40);
        }
    }
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    QLineF ln(QPointF(cannon->getX(), cannon->getY()), event->pos());
    // double angle = -1 * ln.angle();
    // int offset = 30;
    // cannon->setRotation(angle - offset);
}


// getters
int Game::getBlockUnit() {return blockUnit;}
Castle* Game::getCastle() {return castle;}
Cannon* Game::getCannon() {return cannon;}
QGraphicsScene *Game::getScene() {return scene;}
int Game::getLevel() {return level;}


// WorkersClan functions

int Game::getAvailableGroup(int x, int y)
{
    // qDebug() << "group1's ava = " << group1->getAvailability() << ", group's 2 ava = " << group2->getAvailability() << '\n';
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

void Game::spawnEnemies() {
    // // test
    // Enemy* enemy = new Enemy(300, 500, level);
    // scene->addItem(enemy);

    // srand(time(0));
    int i = rand() % 4;
    int randX = rand() % 10, randY = rand() % 10;
    int x= randX*50, y=randY*50;
    Enemy* enemy;
    if(i == 0) {
        // spawn at the top
        enemy = new Enemy(x, 0);
        scene->addItem(enemy);

    }
    else if(i == 1) {
        // spawn at the bottom
        enemy = new Enemy(x, 550);
        scene->addItem(enemy);
    }
    else if(i == 2) {
        // spawn on the left
        enemy = new Enemy(750, y);
        scene->addItem(enemy);
    }
    else {
        // spawn at the right
        enemy = new Enemy(750, y);
        scene->addItem(enemy);
    }

    enemies.append(enemy);



}

void Game::randGifts()
{
    int type = rand() % 3;
    // qDebug() << "Gift's type = " << type;
    int x, y;
    do {
        x = rand() % (800 - 43);
        y = rand() % (600 - 43);
    } while(boardData[y/blockUnit][x/blockUnit] != 0);
    // test
    Gift* g = new Gift(x, y, type);
    scene->addItem(g);
}


void Game::updateTimer() {
    duration--;

    if (duration <= 0) {
        if(level == 4) {
            showWinningWdn();
        } else {
            startNewLevel();
        }
        return;
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

void Game::playSound(QUrl url)
{
    QMediaPlayer* sound = new QMediaPlayer();
    QAudioOutput* audio = new QAudioOutput();
    sound->setAudioOutput(audio);
    sound->setSource(url);
    audio->setVolume(volume);
    sound->play();
}

bool Game::getIsVolSet()
{
    return isVolSet;
}

int Game::getVolume()
{
    return volume;
}

void Game::setVolume(double v)
{
    volume = v/100.0;
    if(!isVolSet) isVolSet = true;
}

void Game::setMap(int mapNumber)
{
    map = mapNumber;
}

int Game::getMap() const
{
    return map;
}

