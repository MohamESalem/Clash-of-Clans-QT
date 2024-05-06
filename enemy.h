#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QKeyEvent>
#include <QList>
#include <QGraphicsScene>
#include <QTimer>
#include <QObject>
#include <QGraphicsItemGroup>
#include "castle.h"
#include "fence.h"
#include "node.h"

using namespace std;
class Enemy: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int imgLen;
    double velocity[5] = {2, 2.5, 3, 3.5, 4.5};
    int healthVal[5] = {45, 55, 60, 80, 90};
    int damageVal[5] = {5, 10, 20, 30, 40};
    int health;
    // images of the enemy in different positions
    QStringList attackImgs;
    QStringList walkImgs;
    // timers
    QTimer* moveTimer;
    QTimer* damageTimer;
    QTimer* attackTimer;
    QTimer* walkTimer;
    Castle* castle;
    int damage;
    HealthBar* healthBar;
    bool isHealthBarShown;
    bool finished = false;
    // test
    // QGraphicsItemGroup* group;

    //contact with the fence
    bool work = false;
    bool contact = false;
    double offsetX = 0;
    double offsetY = 0;
    double STEP_SIZE;
    //graph pointer



public slots:
    void moveRandomly();
    void moveHealthBar();

public:
    Enemy(int,int);
    ~Enemy();
    int getHealth();
    void setHealth(int);
    void decrementHealth(int);
    void incrementHealth(int);
    void attackAnimate();
    void attackFence(Fence*&);
    void attackCastle();
    void updatePath();
    Node* position;
    vector<Node*> path;
    int row;
    int col;
    int curr;

};

#endif // ENEMY_H
