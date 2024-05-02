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

    void addNode(Node*);
    void addEdge(Node* first, Node* second);
    void removeNode(Node* node);
    void removeEdge(Node* first, Node* second);
    Node* findNode(int x, int y);
    bool isEdgeExist(Node* first, Node* second);
    std::vector<Node*> aStarAlgo(Node* first, Node* second);

};

#endif // GRAPH_H
