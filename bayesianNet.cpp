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
float BayesianNet::probability(std::vector<std::string> tokens)
{

    float totalProb = 1;
    std::vector<std::string> tokensAuxiliares;

    for (int i = 0; i < nodes.size(); i++)
    {
        std::cout << "Resolviendo nodo: " << nodes[i].getName() << " con " << nodes[i].cParents() << " padres" << std::endl;
        if (nodes[i].cParents() == 0)
        {
            totalProb *= nodes[i].findProbI(tokens.front());
        }
        else
        {
            for (int x : nodes[i].getParents())
            {
                tokensAuxiliares.push_back(tokens[x]);
            }
            tokensAuxiliares.push_back(tokens[i]);
            totalProb *= nodes[i].findProb(tokensAuxiliares);
            tokensAuxiliares.clear();
        }
    }
    std::cout << "Probabilidad: " << totalProb << std::endl;
    return totalProb;
}

std::string BayesianNet::probabilityInc(std::vector<std::string> tokens)
{

    float totalProb = 1;
    std::vector<std::vector<std::string>> tokensFinales;
    std::vector<std::vector<std::string>> tokensNodo;
    tokensNodo.resize(nodes.size());
    int cantResolv = 0;

    for (int i = 0; i < nodes.size(); i++)
    {
        std::cout << "Resolviendo nodo: " << nodes[i].getName() << " con " << nodes[i].cParents() << " padres" << std::endl;

        if (tokens[i] == "")
        {
            std::set<std::string> uniqueLastElements = nodes[i].uniqueElements(nodes[i].getProbabilities());
            for (auto x : uniqueLastElements)
            {
                tokensNodo[i].push_back(x);
            }
            cantResolv = tokensNodo[i].size();
        }
        else
        {
            tokensNodo[i].push_back(tokens[i]);
            std::cout << "Tokens: " << tokensNodo[i].back() << std::endl;
        }
    }

    for (int i = 0; i < cantResolv; i++)
    {
        for (int j = 0; j < nodes.size(); j++)
        {
            if (tokensNodo[j].size() > 1)
            {
                std::cout << "entro acas" << std::endl;
                tokensFinales[i].push_back(tokensNodo[j].front());
                tokensNodo[j].erase(tokensNodo[j].begin());
            }
            else
            {
                                std::cout << "entro acas2" << std::endl;

                tokensFinales[i].push_back(tokensNodo[j].front());
            }
        }
    }
    float probas = 0;
    for(int x=0;x<tokensFinales.size();x++){
            probas += probability(tokensFinales[x]);
    }
    std::cout << "Probabilidad: " << probas << std::endl;
    return "";
}
bool BayesianNet::isContained(std::vector<std::string> tokens, std::string token)
{
    if (std::find(tokens.begin(), tokens.end(), token) != tokens.end())
    {
        return true;
    }
    return false;
}

void BayesianNet::addParent(int index, int parent)
{
    nodes[index].addParent(parent);
}
