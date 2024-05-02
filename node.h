#ifndef NODE_H
#define NODE_H

class Node
{
    int x;
    int y;
    int strength;
    Node* Next = nullptr; //might use this when finding the path at the end
public:
    Node(int x, int y, int strength);
    void setX(int x);
    void setY(int y);
    void setStrength(int strength);
    int getX() const;
    int getY() const;
    int getStrength() const;
    Node *getNext() const;
    void setNext(Node* nextNode);
    int heuristic;
    int cost;
    Node* parent;
    Node* next;

};

#endif // NODE_H
