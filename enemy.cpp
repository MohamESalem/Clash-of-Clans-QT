#include "enemy.h"
#include "game.h"
#include <QPixmap>
#include <QTimer>
#include <QTime>
#include <qmath.h>
#include <QDebug>
#include <QGraphicsScene>
#include "worker.h"

extern Game* game;

Enemy::Enemy(int x, int y)
{
    // set the picture
    imgLen = 65;
    QPixmap enemyImg(":/images/img/enemy/enemy.png");
    enemyImg = enemyImg.scaled(imgLen, imgLen);
    setPixmap(enemyImg);
    // testing rotation
    setTransformOriginPoint(imgLen/2.0,imgLen/2.0);
    // setRotation(180);
    i = 0;
    setPos(x,y);
    setZValue(3);
    // set the postion
    castle = game->getCastle();
    health = 60;
    damage = 20;
    //**************************************************
    healthBar = new HealthBar(x, y, imgLen, health, true);
    // group = new QGraphicsItemGroup(this);
    // group->addToGroup(this);
    // group->addToGroup(healthBar);
    // group->addToGroup(healthBar->getProgressBar());
    isHealthBarShown = false;
    // healthBar->show();
    // healthBar->setPos(healthBar->x() - 30, healthBar->y());
    // healthBar->getProgressBar()->setPos(healthBar->getProgressBar()->x() - 30, healthBar->getProgressBar()->y());
    // game->getScene()->addItem(group);



    // fill the attackImgs QStringList
    attackImgs.append(":/images/img/enemy/enemy.png");
    attackImgs.append(":/images/img/enemy/1.png");
    attackImgs.append(":/images/img/enemy/2.png");
    attackImgs.append(":/images/img/enemy/3.png");
    attackImgs.append(":/images/img/enemy/4.png");
    // timers
    attackTimer = new QTimer(this);
    connect(attackTimer, &QTimer::timeout, [this]() {
        static int i = 0;
        if(!attackImgs.isEmpty()) setPixmap(QPixmap(attackImgs[i]).scaled(imgLen,imgLen));
        i = (i + 1) % attackImgs.size();
    });
    damageTimer = new QTimer(this);
    moveTimer = new QTimer(this);
    // connect(moveTimer, SIGNAL(timeout()), this, SLOT(moveRandomly()));
    connect(moveTimer, &QTimer::timeout, [this]() {
        this->moveRandomly();

        this->moveHealthBar();

    });
    moveTimer->start(50);

}

Enemy::~Enemy() {attackImgs.clear();}

void Enemy::makeGraph(QString path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    for(int i = 0; i < 12; i++) {
        for(int j = 0; j < 16; j++) {
            QString tmp;
            stream >> tmp;
            tmp.toInt();
            int weight=1;
            if(tmp.toInt()==3) {
                weight = 5;
            }

            else if(tmp.toInt() ==1 || tmp.toInt()==2 || tmp.toInt()==4) {
                weight = 4;
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

        }
    }

}

void Enemy::moveRandomly() {

    // if(!contact) {
    // attackTimer->stop();
    // setPixmap(QPixmap(attackImgs[0]).scaled(imgLen,imgLen));
        // set the destination (either to the castle or the tent)


    // position = graph->findNode(this->row/18,this->col/12);
    //**************************setting path*********************************************************
    // path = graph->aStarAlgo(this->position, graph->findNode(5,5)); //will need to change this to castle position



    setPixmap(QPixmap(attackImgs[0]).scaled(imgLen,imgLen));
    attackTimer->stop();
    int detOffset = 45;
    int detX = castle->getX() + detOffset,
        detY =castle->getY() + detOffset;

    // move to the destination
    const int STEP_SIZE = 3; // this represents the velocity of the worker
    QLineF ln(QPointF(x(), y()), QPointF(detX, detY));
    double angle = -1 * ln.angle();

    double theta = angle; // degrees

    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));
    // healthBar->move(dx, dy);
    setPos(x() + dx, y() + dy);
    // group->setPos(x()+dx, y()+dy);
    // healthBar->setPos(x() + dx, y() + dy);

    QList<QGraphicsItem *> collided_items = collidingItems();
    foreach(auto& item, collided_items) {
        if(typeid(*item) == typeid(Fence)) {
            Fence *f = dynamic_cast<Fence*>(item);
            if(f != NULL && f->getHealth() > 0)
                attackFence(f);
            return;



        } // if the enemy collides with a worker, the worker gets killed immediately
        else if(typeid(*item) == typeid(Worker)) {
          // qDebug() << "Entered\n";
          Worker *w = dynamic_cast<Worker *>(item);
          if (w && !w->isFinished()) {
            // attackAnimate();
            qDebug() << "called\n";
            w->getGroup()->changeIsAlive(w->getClanIndex());
            attackTimer->start(60);
            // w->getHealAnimationTimer()->stop();
            w->die();
            // game->getScene()->removeItem(this);
            // delete item;
            // qDebug() << "worked died!\n";
            }
        }
        else if(typeid(*item) == typeid(Castle)) {
            // game->getCastle()->decrementCurrHealth(damage);
            attackCastle();
            // if(game->getCastle() && game->getCastle()->getCurrHealth()<=0) {
            //     if(game->getCastle()) game->gameOver();
            // }
            // contact = true;
            // mDelay(850);
            return;
        }

        // contact = false;
    }
}

void Enemy::moveHealthBar()
{
    int detOffset = 45;
    int detX = castle->getX() + detOffset,
        detY =castle->getY() + detOffset;

    // move to the destination
    const int STEP_SIZE = 3; // this represents the velocity of the worker
    QLineF ln(QPointF(x(), y()), QPointF(detX, detY));
    double angle = -1 * ln.angle();

    double theta = angle; // degrees

    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));
    // healthBar->move(dx, dy);
    healthBar->setPos(healthBar->x() + dx, healthBar->y() + dy);
    // healthBar->getProgressBar()->setPos(healthBar->getProgressBar()->x() + dx, healthBar->getProgressBar()->y() + dy);
    // setPos(x() + dx, y() + dy);
    // group->setPos(x()+dx, y()+dy);
}

// health functions
void Enemy::setHealth(int x)
{
    health = x;
}

void Enemy::decrementHealth(int x)
{
    health -= x;
    if(!isHealthBarShown) {
        isHealthBarShown = true;
        healthBar->show();
        game->mDelay(80);
    }
    healthBar->decrementCurrHealth(x);
    if(health <= 0) {
        // remove the enemy if its health goes below zero
        if(isHealthBarShown) healthBar->hide();
        game->getScene()->removeItem(this);
        delete this;
    }
}


void Enemy::incrementHealth(int x)
{
    health += x;
}

void Enemy::attackAnimate() {
    for(int i = 0; i < attackImgs.size(); i++) {
        /*if(!game->getScene()->items().isEmpty())*/ setPixmap(QPixmap(attackImgs[i]).scaled(imgLen,imgLen));
        if(i != attackImgs.size() - 1) game->mDelay(100);
    }
    /*if(!game->getScene()->items().isEmpty())*/ setPixmap(QPixmap(attackImgs[0]).scaled(imgLen,imgLen));
}

int Enemy::getHealth()
{
    return health;
}

void Enemy::attackFence(Fence *&f) {
    if(f != NULL && f->getHealth() > 0) {
        disconnect(damageTimer, &QTimer::timeout, nullptr, nullptr);
        connect(damageTimer, &QTimer::timeout, [this,f]() {
            f->decrementHealth(this->damage, this->moveTimer, this->damageTimer);
        });
        moveTimer->stop();
        damageTimer->start(800);
        attackTimer->start(160);
    }
}

void Enemy::attackCastle() {
    disconnect(damageTimer, &QTimer::timeout, nullptr, nullptr);
    connect(damageTimer, &QTimer::timeout, [this]() {
        game->getCastle()->decrementCurrHealth(this->damage);
    });
    moveTimer->stop();
    damageTimer->start(800);
    attackTimer->start(160);
}
