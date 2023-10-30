
#include "node.h"

// Getters

std::string Node::getName()
{
    return name;
}

std::vector<int> Node::getParents()
{
    return parents;
}

Node::DataTable Node::getProbabilities()
{
    return probabilities;
}

void Node::addParent(int index)
{
    parents.push_back(index);
    std::cout << "Añadido padre: " << parents.size() << std::endl;
}

// Setters
void Node::setName(const std::string &newName)
{
    name = newName;
}

void Node::setProbabilities(const DataTable &newProbabilities)
{
    probabilities = newProbabilities;
}
void Node::setTokens(const std::vector<std::string> *tokens)
{
    if (tokens->empty())
    {
        std::cerr << "Error: No se han encontrado tokens" << std::endl;
        return;
    }
    float floatValue;

    try
    {
        // Intenta convertir el último elemento a float.
        floatValue = std::stof(tokens->back());
    }
    catch (const std::invalid_argument &)
    {
        std::cerr << "Error: El último elemento del vector no es convertible a float." << std::endl;
        return;
    }
    std::vector<std::string> stringPart(tokens->begin(), tokens->end() - 1); // Todos los elementos menos el último.
    DataRow row = std::make_pair(stringPart, floatValue);
    this->probabilities.push_back(row);
}
void Node::print()
{
    std::cout << "Nombre: " << name << std::endl;
    std::cout << "Probabilidades: " << std::endl;
    for (int i = 0; i < probabilities.size(); i++)
    {
        std::cout << "Fila " << i << ": ";
        for (int j = 0; j < probabilities[i].first.size(); j++)
        {
            std::cout << probabilities[i].first[j] << " ";
        }
        std::cout << probabilities[i].second << std::endl;
    }
}

int Node::cParents()
{
    return this->parents.size();
}

float Node::findProb(std::vector<std::string> tokens)
{
    for (int i = 0; i < probabilities.size(); i++)
    {
        if (haveSameElements(tokens, probabilities[i].first))
        {
            return probabilities[i].second;
        }
    }
    return 0;
}
bool Node::haveSameElements(std::vector<std::string> v1, std::vector<std::string> v2)
{
    if (v1.size() != v2.size())
    {
        return false;
    }

    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    return v1 == v2;
}

float Node::findProbI(std::string prop)
{
    for (int i = 0; i < probabilities.size(); i++)
    {
        if (probabilities[i].first[0] == prop)
        {
            return probabilities[i].second;
        }
    }
    return 0;
}
std::set<std::string> Node::uniqueElements(DataTable props){

    std::set<std::string> uniqueLastElements;

    for (const DataRow& row : props) {
        if (!row.first.empty()) {
            uniqueLastElements.insert(row.first.back());
        }
    }
    return uniqueLastElements;

}

