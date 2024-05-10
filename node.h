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
    Node(int x, int y, int strength);
    void setX(int x);
    void setY(int y);
    void setStrength(int strength);
    int getX() const;
    int getY() const;
    int getStrength() const;

    void setXPos(int x);
    void setYPos(int y);
    int getXPos() const;
    int getYPos() const;


};

#endif // NODE_H
