#include "worker.h"
#include "game.h"
#include "enemy.h"
#include <QMediaPlayer>
#include <QAudioOutput>

extern Game* game;

Worker::Worker(WorkersClan* g, int index) {
    //spawn audio
    QMediaPlayer* sound = new QMediaPlayer();
    QAudioOutput* audio = new QAudioOutput();
    sound->setAudioOutput(audio);
    sound->setSource(QUrl("qrc:/audio/audio/workerspwan.mp3"));
    audio->setVolume(50);
    // sound->;
    // set the workers' appearance
    imgLen = 50;
    setPixmap(QPixmap(":/images/img/citizen_workers/worker.png").scaled(imgLen, imgLen));
    setTransformOriginPoint(imgLen/2.0, imgLen/2.0);
    offsetX = boundingRect().width()/2.0;
    offsetY = boundingRect().height()/2.0;

    // set the parameters & privat attributes
    group = g;
    clanIndex = index;
    healAbility = 10;
    finished = false;

    // set the position and ZValue
    int offset = 20;
    setPos(group->getTent()->getX() - offset, group->getTent()->getY() + offset);
    setZValue(3);

    // set timers
    moveTimer = new QTimer(this);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    returnTimer = new QTimer(this);
    connect(returnTimer, SIGNAL(timeout()), this, SLOT(returnBack()));
    healTimer = new QTimer(this);
    healAnimationTimer = new QTimer(this);

    // fill healImgs
    healImgs.append(":/images/img/citizen_workers/heal/1.png");
    healImgs.append(":/images/img/citizen_workers/heal/2.png");
    healImgs.append(":/images/img/citizen_workers/heal/3.png");
    healImgs.append(":/images/img/citizen_workers/heal/4.png");
    healImgs.append(":/images/img/citizen_workers/heal/5.png");
    healImgs.append(":/images/img/citizen_workers/heal/6.png");

    // fill dieImgs
    dieImgs.append(":/images/img/citizen_workers/die/2.png");
    dieImgs.append(":/images/img/citizen_workers/die/3.png");
    dieImgs.append(":/images/img/citizen_workers/die/4.png");
    dieImgs.append(":/images/img/citizen_workers/die/5.png");
    dieImgs.append(":/images/img/citizen_workers/die/6.png");

    // start the moveTimer
    STEP_SIZE = 15; // this represents the velocity of the worker
    // qDebug() << "in constructor";
    changePath(group->getDetX(), group->getDetY());
    // for(size_t i = 0; i < path.size(); i++) {
    //     qDebug() << path[i]->getX() << " " << path[i]->getY();
    // }
    moveTimer->start(190);
}

int Worker::getHealAbility(){return healAbility;}
void Worker::setHealAbility(int x) {healAbility = x;}

WorkersClan* Worker::getGroup() {return group;}

QTimer *Worker::getHealAnimationTimer()
{
    return healAnimationTimer;
}
int Worker::getClanIndex() {return clanIndex;}

void Worker::healFence(Fence*f)
{
    if(!group->getAvailability()) {
        connect(healTimer, &QTimer::timeout, [this, f](){
            f->incrementHealth(this->healAbility, this->returnTimer, this->healTimer);
        });
        connect(healAnimationTimer, &QTimer::timeout, [this]() {
            QList<QGraphicsItem *> collided_items = collidingItems();
            foreach(auto& item, collided_items) {
                if(typeid(*item) == typeid(Enemy)) {
                    getGroup()->changeIsAlive(getClanIndex());
                    die();
                    finished = true;
                    return;
                }
            }
            static int i = 0;
            if(!finished) setPixmap(QPixmap(healImgs.at(i)).scaled(imgLen,imgLen));
            i = (i + 1) % healImgs.size();
        });
        healTimer->start(1000);
        healAnimationTimer->start(1000.0/healImgs.size());
    } else {
        returnTimer->start(190);
    }
}

void Worker::die() {
    //audio
    QMediaPlayer* sound = new QMediaPlayer();
    QAudioOutput* audio = new QAudioOutput();
    sound->setAudioOutput(audio);
    sound->setSource(QUrl("qrc:/audio/audio/enemydies.wav"));
    audio->setVolume(50);
    finished = true;
    healAnimationTimer->stop();
    healTimer->stop();
    // sound->play();
    for(int i = 0; i < dieImgs.size(); i++) {
        if(!game->getScene()->items().isEmpty()) setPixmap(QPixmap(dieImgs[i]).scaled(imgLen, imgLen));
        game->mDelay(55);
    }
    game->getScene()->removeItem(this);
    delete this;
    return;
}

bool Worker::isFinished()
{
    return finished;
}

void Worker::changePath(int x, int y)
{
    curr = 1;
    // qDebug() << "before, curr = " << curr;
    // qDebug() << "after, curr = " << curr;
    // qDebug() << "calling changePath()";
    // qDebug() << "x = " << x << ", y = " << y;
    path = game->graph->aStarAlgo(game->graph->findNode(this->y()/50, this->x()/50), game->graph->findNode(y/50,x/50));
    // for(size_t i = 0; i < path.size(); i++) {
    //     qDebug() << path[i]->getX() << ' ' << path[i]->getY();
    // }
    // qDebug() << '\n';
}

void Worker::move()
{
    // qDebug() << "started moving!\n";
    if(group->getAvailability()) {
        // the fence was destroyed
        // qDebug() << "move() first if statement";
        changePath(group->getTent()->getCol() * 50, group->getTent()->getRow() * 50);
        moveTimer->stop();
        returnTimer->start(190);
        return;
    }

    // the workers are under mission
    // stop the animation timer (if it was already started)
    healAnimationTimer->stop();
    setPixmap(QPixmap(":/images/img/citizen_workers/worker.png").scaled(imgLen, imgLen));
    QList<QGraphicsItem *> collided_items = collidingItems();
    foreach(auto& item, collided_items) {
        if(typeid(*item) == typeid(Fence)) {
            Fence* f = dynamic_cast<Fence*>(item);
            // qDebug() << "\nCollided with fence!\n";
            if(f != NULL && f->getHealth() != f->getMaxHealth()) {
                    // qDebug() << "Healing!\n";
                    setPos(x() - 10, y() - 8);
                    moveTimer->stop();
                    healFence(f);
                    return;
            }

        }
    }

    // qDebug() << "moving";
    // // move to the destination
    if(curr < int(path.size())) {
        QLineF ln(QPointF(x() + offsetX, y() + offsetY), QPointF(path[curr]->getXPos(), path[curr]->getYPos()));
        double angle = -1 * ln.angle();
        // qDebug() << "curr = " << curr;
        // qDebug() << path[curr]->getX() << ' ' << path[curr]->getY() << '\n';

        double theta = angle; // degrees

        double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
        double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

        // Handling A* algorithm

        double d1 = pow(path[curr]->getXPos() - path[curr-1]->getXPos(), 2) + pow(path[curr]->getYPos() - path[curr-1]->getYPos(), 2);
        double d2 = pow(x() + offsetX + dx - path[curr-1]->getXPos(), 2) + pow(y() + offsetY + dy - path[curr-1]->getYPos(), 2);

        if(d2 >= d1) {
            curr++;
        }
        setPos(x()+dx, y()+dy);
    } else {
        curr = 1;
    }


}


void Worker::returnBack() {

    // qDebug() << "started going back!\n";

    if(!game->damagedFence.isEmpty()) {
        // qDebug() << "Heading to a new fence\n";
        Fence* f = game->damagedFence.first();
        f->setHealGroup(group);
        f->getHealGroup()->createWorkers(f->getX(), f->getY());
        game->damagedFence.removeFirst();
        group->changeAvailability(false);
    }

    if(!group->getAvailability()) {
        // qDebug() << "in returnBack() second if";
        changePath(group->getDetX(), group->getDetY());
        returnTimer->stop();
        moveTimer->start(190);
        return;
    }

    // stop the animation timer (if it was already started)
    healAnimationTimer->stop();
    setPixmap(QPixmap(":/images/img/citizen_workers/worker.png").scaled(imgLen, imgLen));

    QList<QGraphicsItem *> collided_items = collidingItems();
    foreach(auto& item, collided_items) {
        if(typeid(*item) == typeid(Tent) && dynamic_cast<Tent*>(item) == group->getTent()) {
            returnTimer->stop();
            this->group->changeWorkerPointerToNULL(clanIndex);
            scene()->removeItem(this);
            delete this;
            return;
        }
    }
    if(curr < int(path.size())) {
        QLineF ln(QPointF(x() + offsetX, y() + offsetY), QPointF(path[curr]->getXPos(), path[curr]->getYPos()));
        // QLineF ln(QPointF(x() + offsetX, y() + offsetY), QPointF(group->getTent()->getX(), group->getTent()->getY()));
        double angle = -1 * ln.angle();

        double theta = angle; // degrees

        double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
        double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

        // Handling A* algorithm
        double d1 = pow(path[curr]->getXPos() - path[curr-1]->getXPos(), 2) + pow(path[curr]->getYPos() - path[curr-1]->getYPos(), 2);
        double d2 = pow(x() + offsetX + dx - path[curr-1]->getXPos(), 2) + pow(y() + offsetY + dy - path[curr-1]->getYPos(), 2);

        if(d2 >= d1) {
            curr++;
        }
        setPos(x()+dx, y()+dy);
    } else {
        curr = 1;
        // qDebug() << "curr = " << curr;
    }

}
