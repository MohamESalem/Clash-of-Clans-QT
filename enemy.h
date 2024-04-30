#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QKeyEvent>
#include <QList>
#include <QGraphicsScene>
#include <QTimer>
#include <QObject>
#include "castle.h"
#include "fence.h"

using namespace std;
class Enemy: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int imgLen;
    int i;
    QStringList attackImgs;
    int row;
    int col;
    int health;
    QTimer* moveTimer;
    QTimer* damageTimer;
    QTimer* attackTimer;
    Castle* castle;
    int damage;

    //contact with the fence
    bool work = false;
    bool contact = false;

public slots:
    void moveRandomly();


public:
    Enemy(int x, int y);
    ~Enemy();
    int getHealth();
    void setHealth(int);
    void decrementHealth(int);
    void incrementHealth(int);
    void attackAnimate();
    void mDelay(int);
    void attackFence(Fence*&);
    void attackCastle();
};

#endif // ENEMY_H
