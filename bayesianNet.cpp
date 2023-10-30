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
    return EXIT_FAILURE;
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

float BayesianNet::probabilityInc(std::vector<std::string> tokens)
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
        }
    }
    tokensFinales.resize(cantResolv);
    for (int i = 0; i < cantResolv; i++)
    {
        for (int j = 0; j < nodes.size(); j++)
        {
            if (tokensNodo[j].size() > 1)
            {
                tokensFinales[i].push_back(tokensNodo[j].front());
                tokensNodo[j].erase(tokensNodo[j].begin());
            }
            else
            {
                tokensFinales[i].push_back(tokensNodo[j].front());
            }
        }
    }
    float probas = 0;
    for(int x=0;x<tokensFinales.size();x++){
            probas += probability(tokensFinales[x]);
    }
    std::cout << "Probabilidad Final: a[" << probas << "]"<< std::endl;
    return probas;
}
float BayesianNet::resolveX(std::vector<std::string> tokens){

    std::vector<std::vector<std::string>> tokensFinales;
    std::vector<std::vector<std::string>> tokensNodo;
    tokensNodo.resize(nodes.size());
    int cantResolv = 0;

    for (int i = 0; i < nodes.size(); i++)
    {
        std::cout << "Resolviendo X: " << nodes[i].getName() << " con " << nodes[i].cParents() << " padres" << std::endl;

        if (tokens[i] == "x")
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
        }
    }

    tokensFinales.resize(cantResolv);
    for (int i = 0; i < cantResolv; i++)
    {
        for (int j = 0; j < nodes.size(); j++)
        {
            if (tokensNodo[j].size() > 1)
            {
                tokensFinales[i].push_back(tokensNodo[j].front());
                tokensNodo[j].erase(tokensNodo[j].begin());
            }
            else
            {
                tokensFinales[i].push_back(tokensNodo[j].front());
            }
        }
    }
    std::vector<float> propsFinales;
    for(int i = 0 ; i < tokensFinales.size(); i++){
        propsFinales.push_back(probabilityInc(tokensFinales[i]));
    }
    std::vector<float> propsEstandarizados;
    float a = 1/std::accumulate(propsFinales.begin(), propsFinales.end(), 0.0f);

    std::cout << "Usando a: " << a << std::endl;



    std::cout << "a <" ;
    for(int i=0; i<propsFinales.size();i++)
    {
        std::cout << propsFinales[i];
        if(i != propsFinales.size()-1)
            std::cout << ",";
    }
    std::cout << ">" << std::endl;

   

    std::cout << "<" ;
    for(int i=0; i<propsFinales.size();i++)
    {
        std::cout << a * propsFinales[i];
        if(i != propsFinales.size()-1)
            std::cout << ",";
    }
    std::cout << ">" << std::endl;

    
    
    
    
    return 0;

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
