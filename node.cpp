
#include "node.h"

// Getters

std::string Node::getName()
{
    return name;
}

std::vector<Node> Node::getParents()
{
    return parents;
}

Node::DataTable Node::getProbabilities()
{
    return probabilities;
}

// Setters
void Node::setName(const std::string &newName)
{
    name = newName;
}

void Node::setParents(const std::vector<Node> &newParents)
{
    parents = newParents;
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
