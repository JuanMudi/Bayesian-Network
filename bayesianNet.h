#ifndef BAYESIAN_NET_H
#define BAYESIAN_NET_H

#include <iostream>
#include <string>
#include <vector>
#include "node.h"

class BayesianNet {
public:
    BayesianNet();
    Node getNodeI(int index);
    int getNodeN(std::string name);
    void addNode(Node node);
    void addEdge(int parentIndex, int childIndex); 
    void removeNode(int index);
    int size();

private:
    std::vector<Node> nodes;
    std::vector<std::vector<int>> edges;
};

#endif // BAYESIAN_NET_H
