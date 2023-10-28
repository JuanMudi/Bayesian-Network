#include "bayesianNet.h"

BayesianNet::BayesianNet() {
    nodes = std::vector<Node>();
    edges = std::vector<std::vector<int>>();
}
    void BayesianNet::addNode(Node node){
        nodes.push_back(node);

    }
    void BayesianNet::removeNode(int index){

    }
    Node BayesianNet::getNodeI(int index){
        Node node = Node();
        return node;

    }
    int BayesianNet::getNodeN(std::string name){
        return 0;

    }
    void BayesianNet::addEdge(int parentIndex, int childIndex){
        
    }
    int BayesianNet::size(){
        return nodes.size();
    }