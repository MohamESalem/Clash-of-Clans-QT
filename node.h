#ifndef NODE_H
#define NODE_H

class Node
{
    int x;
    int y;
    int strength;
public:
    Node(int x, int y, int strength);
    void setX(int x);
    void setY(int y);
    void setStrength(int strength);
    int getX() const;
    int getY() const;
    int getStrength() const;
    int xPos;
    int yPos;


};

#endif // NODE_H
