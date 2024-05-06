#include "fence.h"
#include "game.h"
#include "worker.h"
#include <QMediaPlayer>
#include <QAudioOutput>

extern Game* game;

Fence::Fence(int x, int y) {
    QPixmap fenceImg(":/images/img/fence.png");
    fenceImg = fenceImg.scaled(game->getBlockUnit(), game->getBlockUnit());
    setPixmap(fenceImg);
    this->x = x;
    this->y = y;
    setPos(this->x, this->y);
    maxHealth = 60;
    health = maxHealth;
    healGroup = NULL;
    finished = false;
    // set the healthBar
    healthBar = new HealthBar(x, y, game->getBlockUnit(), maxHealth);
    isHealthBarShown = false;
}

int Fence::getX() {return x;}
int Fence::getY() {return y;}

void Fence::setHealth(int x)
{
    health = x;
}

void Fence::decrementHealth(int x, QTimer*& moveTimer, QTimer*&damageFence, QTimer*& walkTimer)
// PASS THEM BE REFERENCE FOR ENEMY DAMAGING FENCE
// LOOK AT DECREMENTHEALTH() IN CASTLE CLASS
{
    QMediaPlayer* sound = new QMediaPlayer();
    QAudioOutput* audio = new QAudioOutput();
    sound->setAudioOutput(audio);
    sound->setSource(QUrl("qrc:/audio/audio/enemydamagefence.wav"));
    audio->setVolume(50);

    if(finished) {
        game->updateEnemyPath();
        // damageFence->stop();
        // moveTimer->start(50);
        // walkTimer->start(100);
    } else {
        health -= x;
        // sound->play();
        if(!isHealthBarShown) {
            healthBar->show();
            isHealthBarShown = true;
            game->mDelay(300);
        }
        healthBar->decrementCurrHealth(x);
        // if(this) qDebug() << "after, Finished = " << finished;
        // qDebug() << getX() << ' ' << getY() << '\n';
        // qDebug() << "Health = " << health << '\n';

        if(health > 0) {
            if(healGroup == NULL) {
                int ava = game->getAvailableGroup(this->x, this->y);
                // qDebug() << "ava = " << ava << '\n';
                if(ava == 1) {
                    healGroup = game->getGroup1();
                    healGroup->changeAvailability(false);
                    healGroup->createWorkers(this->x, this->y);
                } else if(ava == 2) {
                    healGroup = game->getGroup2();
                    healGroup->changeAvailability(false);
                    healGroup->createWorkers(this->x, this->y);
                } else if(ava == 0) {
                    if(!game->damagedFence.contains(this)) {
                        game->damagedFence.append(this);
                    }
                } // otherwise ava = -1, i.e., no group are availble, don't do anything
            }
        }
        else {
            // enemy destroys the fence when the fence's health goes below zero
            sound->play();
            if(healGroup) healGroup->changeAvailability(true);
            if(isHealthBarShown) healthBar->hide();
            // qDebug() << "Removing this fence: " << getX() << ' ' << getY() << '\n';
            if(!finished) scene()->removeItem(this);
            if(game->damagedFence.contains(this)) game->damagedFence.removeAll(this);

            // damageFence->stop();
            // moveTimer->start(50);
            // walkTimer->start(200);

            finished = true;
            game->graph->editStrength(this->getY()/50,this->getX()/50,1);
            game->updateEnemyPath();
            if(!finished) delete this;
            return;
        }
    }

}

void Fence::decrementHealth(int x)
// PASS THEM BE REFERENCE FOR ENEMY DAMAGING FENCE
// LOOK AT DECREMENTHEALTH() IN CASTLE CLASS
{
    QMediaPlayer* sound = new QMediaPlayer();
    QAudioOutput* audio = new QAudioOutput();
    sound->setAudioOutput(audio);
    sound->setSource(QUrl("qrc:/audio/audio/enemydamagefence.wav"));
    audio->setVolume(50);

    if(finished) {
        game->updateEnemyPath();
        // damageFence->stop();
        // moveTimer->start(50);
    } else {
        health -= x;
        // sound->play();
        if(!isHealthBarShown) {
            healthBar->show();
            isHealthBarShown = true;
            game->mDelay(300);
        }
        healthBar->decrementCurrHealth(x);
        // if(this) qDebug() << "after, Finished = " << finished;
        // qDebug() << getX() << ' ' << getY() << '\n';
        // qDebug() << "Health = " << health << '\n';

        if(health > 0) {
            if(healGroup == NULL) {
                int ava = game->getAvailableGroup(this->x, this->y);
                // qDebug() << "ava = " << ava << '\n';
                if(ava == 1) {
                    healGroup = game->getGroup1();
                    healGroup->changeAvailability(false);
                    healGroup->createWorkers(this->x, this->y);
                } else if(ava == 2) {
                    healGroup = game->getGroup2();
                    healGroup->changeAvailability(false);
                    healGroup->createWorkers(this->x, this->y);
                } else if(ava == 0) {
                    if(!game->damagedFence.contains(this)) {
                        game->damagedFence.append(this);
                    }
                } // otherwise ava = -1, i.e., no group are availble, don't do anything
            }
        }
        else {
            // enemy destroys the fence when the fence's health goes below zero
            // sound->play();
            if(healGroup) healGroup->changeAvailability(true);
            if(isHealthBarShown) healthBar->hide();
            // qDebug() << "Removing this fence: " << getX() << ' ' << getY() << '\n';
            if(!finished) scene()->removeItem(this);
            if(game->damagedFence.contains(this)) game->damagedFence.removeAll(this);

            // damageFence->stop();
            // moveTimer->start(50);
            finished = true;
            game->graph->editStrength(this->getY()/50,this->getX()/50,1);
            game->updateEnemyPath();
            if(!finished) delete this;
            return;
        }
    }

}


void Fence::incrementHealth(int x, QTimer*& returnTimer, QTimer*& healTimer)
{
    Worker* w = dynamic_cast<Worker*>(returnTimer->parent());
    if(finished) {
        // qDebug() << "at the start of increment health!";
        w->changePath(w->getGroup()->getTent()->getCol() * 50, w->getGroup()->getTent()->getRow() * 50);
        healTimer->stop();
        returnTimer->start(190);
    } else {

        if(health == maxHealth) {
            // qDebug() << "second else first if";
            w->changePath(w->getGroup()->getTent()->getCol() * 50, w->getGroup()->getTent()->getRow() * 50);
            healTimer->stop();
            returnTimer->start(190);
        } else if(!finished && health + x < maxHealth) {
            health += x;
            healthBar->incrementCurrHealth(x);
            // qDebug() << "Improving Health\n";
        }
        else {

            health = maxHealth;
            // qDebug() << "health is maximum";
            healGroup = NULL;
            healthBar->incrementCurrHealth(x);
            game->mDelay(125);
            healthBar->hide();

            // code to check if there are other damaged fences before returning back
            // if(!game->damagedFence.isEmpty()) {
                // qDebug() << "Heading to a new fence\n";
                // Fence* f = game->damagedFence.first();
                // f->setHealGroup(w->getGroup());
                // f->getHealGroup()->createWorkers(f->getX(), f->getY());
                // game->damagedFence.removeFirst();
            // } else {
            w->getGroup()->changeAvailability(true);
            // }

            // qDebug() << "at the end of increment fence's health";
            w->changePath(w->getGroup()->getTent()->getCol() * 50, w->getGroup()->getTent()->getRow() * 50);
            healTimer->stop();
            returnTimer->start(190);
        }
    }
}



int Fence::getHealth() {return health;}
int Fence::getMaxHealth() {return maxHealth;}
WorkersClan* Fence::getHealGroup() {return healGroup;}
void Fence::setHealGroup(WorkersClan* g) {healGroup = g;}

bool Fence::isFinished()
{
    return finished;
}
