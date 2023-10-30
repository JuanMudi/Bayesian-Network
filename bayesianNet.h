#ifndef BAYESIAN_NET_H
#define BAYESIAN_NET_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <numeric>
#include "node.h"

class BayesianNet
{
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
    float probability(std::vector<std::string> tokens);
    float probabilityInc(std::vector<std::string> tokens);
    void addParent(int index, int parent);
    bool isContained(std::vector<std::string> tokens, std::string token);
    float resolveX(std::vector<std::string> tokens);


private:
    std::vector<Node> nodes;
    std::vector<std::list<int>> edges;
};

#endif // BAYESIAN_NET_H
