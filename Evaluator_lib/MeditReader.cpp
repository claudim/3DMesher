#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "MeditReader.h"
#include <regex>


void MeditReader::readVertices(std::string aFileName, std::vector<std::array<double, 3>> &vertices) {

    std::regex regex ("([-]?\\d+\\.?\\d* [-]?\\d+\\.?\\d* [-]?\\d+\\.?\\d*)");
    std::string line;
    std::ifstream input(aFileName);
    std::array<double, 3> vertex{};
    while (getline(input, line))
    {
        if (line == "Quadrilaterals")
            break;
        if(std::regex_search(line,regex)) {
            // Output the text from the file
            std::cout << line << std::endl;
            std::stringstream ss(line);
            double temp;
            int i = 0;
            while ((ss >> temp) || i < 3)
            {
                vertex[i] = temp;
                i++;
            }
            vertices.emplace_back(vertex);
        }
    }

    // Close the file
    input.close();


}
