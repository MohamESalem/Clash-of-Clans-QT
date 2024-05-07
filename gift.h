#ifndef GIFT_H
#define GIFT_H

#include <QGraphicsPixmapItem>

class Gift : public QGraphicsPixmapItem
{
private:
    int type; // a value of 0, 1, or 2
public:
    Gift(int,int,int);
    void utilize();
};

#endif // GIFT_H
