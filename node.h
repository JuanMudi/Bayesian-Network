
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


#ifndef NODE_H
#define NODE_H

/**
 * @brief A class representing a node in a Bayesian network.
 * 
 */
class Node {
    
    using DataRow = std::pair<std::vector<std::string>, float>;
    using DataTable = std::vector<DataRow>;
private:

    std::string name;
    std::vector<int> parents;
    DataTable probabilities;

public:
    std::string getName();
    DataTable getProbabilities();
    void addParent(int index);
    void setName(const std::string& newName);
    void setParents(const std::vector<Node>& newParents);
    void setProbabilities(const DataTable& newProbabilities);
    void setTokens(const std::vector<std::string> *tokens);
    int cParents ();
    float findProb (std::vector<std::string> tokens);   
    void print();
    bool haveSameElements(std::vector<std::string> v1, std::vector<std::string> v2);
    float findProbI (std::string prop);
    std::vector<int> getParents();
};

#endif // NODE_H

    


    

