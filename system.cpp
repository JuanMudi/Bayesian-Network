
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "bayesianNet.h"
#include <vector>

#define FILE "E:\\IA\\Bayesian-Network-1\\Pruebas\\ex1.txt"
#define EDGES "E:\\IA\\Bayesian-Network-1\\Pruebas\\ex1_edges.txt"

int main()
{
    std::cout << "\n##################################################################" << std::endl;

    std::cout << "CREANDO RED BAYESIANA" << std::endl;

    std::cout << "##################################################################" << std::endl;

    BayesianNet net = BayesianNet();

    std::ifstream file(FILE);
    if (!file.is_open())
    {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return 1;
    }

    std::vector<std::string> tokens;
    std::string line = "";
    std::istringstream ss(line);
    std::string token = "";
    std::vector<std::string> names;

    std::getline(file, line);
    names.push_back(line);
    tokens.clear();
    Node node = Node();
    while (std::getline(file, line))
    {
        //  Si es una línea con '&', significa que ha comenzado una nueva sección.
        if (line == "&")
        {
            std::getline(file, line);

            names.push_back(line);
            node.setName(names.front());
            names.erase(names.begin());
            net.addNode(node);
            tokens.clear(); // Limpia los tokens para la próxima sección.
            node = Node();
            if (line == "*")
            {
                std::cout << "Final del archivo" << std::endl;
                break;
            }
            continue;
        }
        else
        {
            ss.clear();   // Limpiar el estado de ss
            ss.str(line); // Ajustar el contenido de ss a la línea actual

            // Tokenizar la línea
            while (std::getline(ss, token, ','))
            {
                token.erase(0, token.find_first_not_of(" "));
                token.erase(token.find_last_not_of(" ") + 1);
                tokens.push_back(token);
            }
            node.setTokens(&tokens);
            tokens.clear();
        }
    }
    file.close();
    net.print();

    std::cout << "\nRED BAYESIANA CREADA CON " << net.size() << " NODOS" << std::endl;

    std::cout << "\n##################################################################" << std::endl;

    std::cout << "CREANDO RELACIONES ENTRE NODOS" << std::endl;

    std::cout << "##################################################################" << std::endl;

    net.createEdges(net.size());
    file.open(EDGES);
    if (!file.is_open())
    {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return 1;
    }
    tokens.clear();
    while (std::getline(file, line))
    {
        ss.clear();   // Limpiar el estado de ss
        ss.str(line); // Ajustar el contenido de ss a la línea actual

        // Tokenizar la línea
        while (std::getline(ss, token, '/'))
        {
            token.erase(0, token.find_first_not_of(" "));
            token.erase(token.find_last_not_of(" ") + 1);
            tokens.push_back(token);
        }
        net.addEdge(net.getNodeN(tokens[0]), net.getNodeN(tokens[1]));


        int index = net.getNodeN(tokens[1]);
        int index2 = net.getNodeN(tokens[0]);
        net.addParent(index,index2);   

        std::cout << "Agregando arista entre " << tokens[0] << " y " << tokens[1] << std::endl;
        tokens.clear();
    }
    file.close();

    std::cout << "\n##################################################################" << std::endl;

    std::cout << "RED BAYESIANA GENERADA" << std::endl;

    std::cout << "##################################################################" << std::endl;

    net.printGraph();

    tokens.clear();
    std::string prop = "light,no,delayed,miss";

    ss.clear();   // Limpiar el estado de ss
    ss.str(prop); // Ajustar el contenido de ss a la línea actual

        // Tokenizar la línea
        while (std::getline(ss, token, ','))
        {
            token.erase(0, token.find_first_not_of(" "));
            token.erase(token.find_last_not_of(" ") + 1);
            tokens.push_back(token);
        }
    
    std::cout << "\n##################################################################" << std::endl;

    std::cout << "SOLUCIONANDO RED BAYESIANA SIN INCOGNITAS" << std::endl;

    std::cout << "##################################################################" << std::endl;
    std::cout << net.probability(tokens) << std::endl;
    } 
