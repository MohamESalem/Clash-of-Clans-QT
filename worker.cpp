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
    sound->play();
    // set the workers' appearance
    imgLen = 50;
    setPixmap(QPixmap(":/images/img/citizen_workers/worker.png").scaled(imgLen, imgLen));
    setTransformOriginPoint(imgLen/2.0, imgLen/2.0);

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
    moveTimer->start(250);
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
        returnTimer->start(250);
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
    for(int i = 0; i < dieImgs.size(); i++) {
        if(!game->getScene()->items().isEmpty()) setPixmap(QPixmap(dieImgs[i]).scaled(imgLen, imgLen));
        game->mDelay(85);
    }
    game->getScene()->removeItem(this);
    delete this;
    return;
}

bool Worker::isFinished()
{
    return finished;
}

void Worker::move() {

    if(group->getAvailability()) {
        // the fence was destroyed
        moveTimer->stop();
        returnTimer->start(250);
        return;
    } else {
        // the workers are under mission
        // stop the animation timer (if it was already started)
        healAnimationTimer->stop();
        setPixmap(QPixmap(":/images/img/citizen_workers/worker.png").scaled(imgLen, imgLen));
        QList<QGraphicsItem *> collided_items = collidingItems();
        foreach(auto& item, collided_items) {
            if(typeid(*item) == typeid(Fence)) {

                Fence* f = dynamic_cast<Fence*>(item);
                if(f != NULL && f->getHealth() != f->getMaxHealth()) {
                        moveTimer->stop();
                        healFence(f);
                        return;
                }

            }
        }
    }

    // // move to the destination
    const int STEP_SIZE = 20; // this represents the velocity of the worker
    QLineF ln(QPointF(x(), y()), QPointF(group->getDetX(), group->getDetY()));
    double angle = -1 * ln.angle();

    double theta = angle; // degrees

    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);

}


void Worker::returnBack() {

    if(!group->getAvailability()) {
        returnTimer->stop();
        moveTimer->start(250);
        return;
    }

    // stop the animation timer (if it was already started)
    healAnimationTimer->stop();
    setPixmap(QPixmap(":/images/img/citizen_workers/worker.png").scaled(imgLen, imgLen));

    int tentX = group->getTent()->getX(),
        tentY = group->getTent()->getY();

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

    const int STEP_SIZE = 20; // this rep resents the velocity of the worker
    QLineF ln(QPointF(x(), y()), QPointF(tentX, tentY));

    double angle = -1 * ln.angle();

    double theta = angle; // degrees

    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);
}
