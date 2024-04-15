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
using namespace std;
class Enemy: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int row;
    int col;
    int health;
    QTimer* moveTimer;
    Castle* castle;
    int damage;

public slots:
    void moveRandomly();


public:
    Enemy(int x, int y);
    int getHealth();
    void setHealth(int);
    void decrementHealth(int);
    void incrementHealth(int);
};

#endif // ENEMY_H
