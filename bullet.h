#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int damage;
public:
    Bullet();
    int getDamage();
    void setDamage(int);
public slots:
    void move();
};

#endif // BULLET_H
