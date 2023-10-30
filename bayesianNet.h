#ifndef BAYESIAN_NET_H
#define BAYESIAN_NET_H

#include <iostream>
#include <string>
#include <vector>
#include <list> 
#include "node.h"

class BayesianNet {
public:
    Node getNodeI(int index);
    int getNodeN(std::string name);
    void addNode(Node node);
    void addEdge(int v, int w); 
    void removeNode(int index);
    int size();
    void print();
    void createEdges(int n);
    void printProbabilities(int index);
    void printGraph();
    std::string probability(std::vector<std::string> tokens);
    void addParent(int index, int parent);
    
private:
    std::vector<Node> nodes;
    std::vector<std::list<int>> edges;
};

#endif // BAYESIAN_NET_H
