#ifndef CASTLE_H
#define CASTLE_H

#include <QGraphicsPixmapItem>

class Castle : public QGraphicsPixmapItem
{
private:
    int health;
public:
    Castle();
    void setHealth(int);
    void decrementHealth(int);
    void incrementHealth(int);
    int getHealth();
    // add castle coordinates
    // add getters and setters
    // getX()
    // getY()
};

#endif // CASTLE_H
