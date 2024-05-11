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
    double velocity[5] = {2.5, 2.75, 3, 3.25, 3.4};
    int healthVal[5] = {50, 55, 60, 70, 80};
    int damageVal[5] = {5, 10, 20, 25, 30};
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
    vector<Node*> path;
    // test
    // QGraphicsItemGroup* group;

    //contact with the fence
    bool work = false;
    bool contact = false;
    double offsetX = 0;
    double offsetY = 0;
    double STEP_SIZE;

    int row;
    int col;
    int curr;


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
    void setRow(int r);
    void setCol(int c);
    void setCurr(int c);
    int getRow() const;
    int getCol() const;
    int getCurr() const;
};

#endif // ENEMY_H
