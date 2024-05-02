#include "graph.h"
#include <cmath>
#include <queue>
#include <set>
#include <algorithm>

int Graph::getWeight(Node *first, Node *second) const
{
    int x1=first->getX();
    int x2=second->getX();
    int y1=first->getY();
    int y2=second->getY();
    int value = (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);

    int weight = std::sqrt(value)*(first->getStrength()+second->getStrength());
    return weight;
}

void Graph::addNode(Node* node)
{
    adjList[node] = std::vector<std::pair<Node*, int>>();
}

void Graph::addEdge(Node *first, Node *second)
{
    int weight = getWeight(first, second);

    adjList[first].push_back(std::make_pair(second, weight));
}

void Graph::removeNode(Node *node)
{
    for (auto it = adjList.begin(); it != adjList.end(); ++it) {
        for (auto jt = it->second.begin() ; jt != it->second.end(); ++jt) {
            if(jt->first == node) {
                removeEdge(it->first, jt->first);
                it->second.erase(jt);

                break;
            }
        }
    }

    adjList.erase(node);
}

void Graph::removeEdge(Node *first, Node *second)
{
    for (auto it = adjList[first].begin(); it != adjList[first].end(); ++it) {
        if(it->first== second) {
            adjList[first].erase(it);
        }
    }
}

std::vector<Node*> Graph::aStarAlgo(Node* start, Node* goal)
{
    std::priority_queue<std::pair<int, Node*>> openList; //priority queue to store discovered nodes but not processed yet
    // in the pair the first element is the priority score
    std::set<Node*> closedList; //the closedlist is for the processed nodes
    std::map<Node*, Node*> cameFrom; //to reconstruct the path from the goal node to the start node
    std::map<Node*, int> gScore; //cost from the starting node; it's updated for each node if a lower cost path is found
    std::map<Node*, int> fScore; //the estimated total cost from the start node to the goal node

    openList.push(std::make_pair(0, start));

    gScore[start] = 0;

    fScore[start] = getWeight(start, goal); //getting the eucledian distance between start and goal and multiply it by the strength

    while (!openList.empty()) {
        Node* currentNode = openList.top().second;
        openList.pop();

        if (currentNode == goal) {
            // Path found, reconstruct the path
            std::vector<Node*> path;
            Node* temp = currentNode;
            while (temp!= nullptr) {
                path.push_back(temp); //adding the node to the path
                temp = cameFrom[temp]; //getting the node it came from
            }
            std::reverse(path.begin(), path.end()); //the nodes are constructuted in reverse order
            return path;
        }

        closedList.insert(currentNode); //going to be processed

        for (auto& neighbor : adjList[currentNode]) {
            Node* neighborNode = neighbor.first; //getting the neighbor node and its weight
            int weight = neighbor.second;

            //checking if this node has already been processed or not
            //if yes, it'll skip it
            if (closedList.find(neighborNode)!= closedList.end()) {
                continue;

            }
            //gScore[currentNode] is the current gScore of the currentNode, which representes the cost
            //of the shortest path from the start node to the currentNode
            //and the weight is the cost of the edge between currentNode and neighbore node (check above after the for loop)
            int tentativeGScore = gScore[currentNode] + weight; //this is the estimated cost of reaching the neighboring node from the start node


            //checking whether the neighboreNode is in in gScore and if the estimated cost is less than that of neighboreNode
            if (gScore.find(neighborNode) == gScore.end() || tentativeGScore < gScore[neighborNode]) {
                cameFrom[neighborNode] = currentNode; //if so, currentNode will be the parent of the neighboreNode
                gScore[neighborNode] = tentativeGScore;// and the gScore of the neighboreNode will be updated
                fScore[neighborNode] = tentativeGScore + getWeight(neighborNode, goal); //and the fScore will be updated as well
                openList.push(std::make_pair(fScore[neighborNode], neighborNode)); //adding neighboreNode to the openList with its fScore to be processed later (marked found)
            }
        }
    }

    // No path found
    return {};
}


