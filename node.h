#ifndef NODE_H
#define NODE_H

class Node
{
    int x;
    int y;
    int strength;
    int xPos;
    int yPos;
public:
    Node(int,int,int);
    void setX(int);
    void setY(int);
    void setStrength(int);
    int getX() const;
    int getY() const;
    int getStrength() const;
    void setXPos(int);
    void setYPos(int);
    int getXPos() const;
    int getYPos() const;
};

#endif // NODE_H
