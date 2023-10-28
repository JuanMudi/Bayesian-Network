
#include <iostream>
#include <string>
#include <vector>


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
    std::vector<Node> parents;
    DataTable probabilities;

public:
    std::string getName();
    std::vector<Node> getParents();
    DataTable getProbabilities();
    void setName(const std::string& newName);
    void setParents(const std::vector<Node>& newParents);
    void setProbabilities(const DataTable& newProbabilities);
    void setTokens(const std::vector<std::string> *tokens);
};

#endif // NODE_H

    


    

