
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "bayesianNet.h"
#include <vector>

#define FILE "E:\\IA\\Pruebas\\ex1.txt"

int main()
{
    std::cout << "CREANDO RED BAYESIANA" << std::endl;
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
    std::string name = "";

    std::getline(file, line);
    std::cout << "Nombre: " << line << std::endl;
    name = line;
    tokens.clear();
    Node node = Node();
    while (std::getline(file, line))
    {
        // std::cout << "While: " <<line << std::endl;
        //  Si es una línea con '&', significa que ha comenzado una nueva sección.
        if (line == "&")
        {
            std::getline(file, line);
            if (line == "*")
            {
                std::cout << "Final del archivo" << std::endl;
                break;
            }
            name = line;
            //std::cout << "Nombre: " << name << std::endl;
            node.setName(name);
            net.addNode(node);
            tokens.clear(); // Limpia los tokens para la próxima sección.
            node = Node();  
            continue;
        }
        else
        {
            ss.clear(); // Limpiar el estado de ss
            ss.str(line); // Ajustar el contenido de ss a la línea actual

            //std::cout << "Linea: " << line << std::endl;     
            // Tokenizar la línea
            while (std::getline(ss, token, ','))
            {
                token.erase(0, token.find_first_not_of(" "));
                token.erase(token.find_last_not_of(" ") + 1);
                tokens.push_back(token);
            }
            //std::cout << "Tokens: " << tokens.size() << std::endl;
            node.setTokens(&tokens);
            tokens.clear(); 

        }
    }
    net.addNode(node);

    file.close();

    std::cout << "RED BAYESIANA CREADA CON " << net.size() << " NODOS" << std::endl;
}
