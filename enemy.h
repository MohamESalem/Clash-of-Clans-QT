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
#include "graph.h"

using namespace std;
class Enemy: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int imgLen;
    int i;
    QStringList attackImgs;
    // int row;
    // int col;
    int health;
    QTimer* moveTimer;
    QTimer* damageTimer;
    QTimer* attackTimer;
    Castle* castle;
    int damage;
    HealthBar* healthBar;
    bool isHealthBarShown;
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
    Enemy(int x, int y);
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
