#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <map>
#include "node.h"
class Graph
{
    std::map<Node*, std::vector<std::pair<Node*, int>>> adjList;
public:
    Graph();
    Node* makeNode(int,int,int);
    void addNode(Node*);
    void addEdge(Node*,Node*);
    void removeNode(Node*);
    void removeEdge(Node*,Node*);
    void editEdge(Node*,Node*);
    Node* findNode(int,int);
    bool isEdgeExist(Node*,Node*);
    std::vector<Node*> aStarAlgo(Node*,Node*);
    int getWeight(Node*,Node*) const;
    std::vector<Node*> getNeighbors(Node*);
    void editStrength(int,int,int);

};

#endif // GRAPH_H
