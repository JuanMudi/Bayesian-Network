#include "bayesianNet.h"

void BayesianNet::addNode(Node node)
{
    nodes.push_back(node);
}
void BayesianNet::removeNode(int index)
{
}
Node BayesianNet::getNodeI(int index)
{
    return nodes[index];
}
int BayesianNet::getNodeN(std::string name)
{
    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i].getName() == name)
        {
            return i;
        }
    }
    EXIT_FAILURE;
}
void BayesianNet::addEdge(int v, int w)
{
    edges[v].push_back(w); // Agrega w a la lista de v
    return;
}
int BayesianNet::size()
{
    return nodes.size();
}
void BayesianNet::print()
{
    for (int i = 0; i < nodes.size(); i++)
    {
        printProbabilities(i);
    }
}
void BayesianNet::printProbabilities(int index)
{
    nodes[index].print();
}
void BayesianNet::createEdges(int n)
{
    edges.resize(n);
}
void BayesianNet::printGraph()
{
    for (int i = 0; i < nodes.size(); i++)
    {
        std::cout << nodes[i].getName() << " -> ";
        for (auto x : edges[i])
        {
            std::cout << nodes[x].getName() << " ";
        }
        std::cout << std::endl;
    }
}
std::string BayesianNet::probability(std::vector<std::string> tokens)
{


    float totalProb = 1;
    std::vector<std::string> tokensAuxiliares;
    

    for (int i = 0; i < nodes.size(); i++)
    {
        std::cout << "Resolviendo nodo: " << nodes[i].getName() << " con " << nodes[i].cParents() << " padres"<< std::endl;
        if (nodes[i].cParents() == 0)
        {
            totalProb *= nodes[i].findProbI(tokens.front());
        }
        else
        {
            for(int x : nodes[i].getParents()){
                tokensAuxiliares.push_back(tokens[x]);
            }
            tokensAuxiliares.push_back(tokens[i]);
            totalProb *= nodes[i].findProb(tokensAuxiliares);
            tokensAuxiliares.clear();
        }
        
    }
    std::cout << "Probabilidad: " << totalProb << std::endl;
    return "";
}

void BayesianNet::addParent(int index, int parent){
    nodes[index].addParent(parent);
}

