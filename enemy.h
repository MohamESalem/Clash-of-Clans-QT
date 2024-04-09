#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QKeyEvent>
#include <QList>
#include <QGraphicsScene>
#include <QTimer>
#include <QObject>
using namespace std;
class Enemy: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int row;
    int col;
    int health;
    QString k; //movement of enemy

public:
    Enemy(int x, int y);
    void moveRandomly();
    void setHealth(int);
    void decrementHealth(int);
    void incrementHealth(int);
    int getHealth();
};

#endif // ENEMY_H
