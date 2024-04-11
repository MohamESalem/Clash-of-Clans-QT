#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "castle.h"
#include "tent.h"

class Worker : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int healAbility;
    QTimer* moveTimer;
    QTimer* healTimer;
    Castle* castle;
    Tent* tent;
public:
    Worker();
    int getHealAbility();
    void setHealAbility(int);
    void healCastle();
public slots:
    void move();
};

#endif // WORKER_H
