#include "CitiesMatrixPrinter.hpp"

#include <iostream>

using namespace std;

#define RST  "\x1B[0m"
#define KRED  "\x1B[41m"
#define KBLU  "\x1B[44m"

void CitiesMatrixPrinter::print(const CitiesMatrix &graph)
{
    const auto &count = graph.get_cities_number();
    const auto &vertices = graph.get_cities_number();

    if (vertices == 0) {
        std::cout << KRED << "Graf jest pusty!" << RST << std::endl;
        return;
    }

    std::cout << "   " << KRED;
    for (size_t j = 0; j < count; j++) {
        std::cout << j << "  ";

        if (j < 10)
            std::cout << " ";
    }
    std::cout << RST << std::endl;

    for (size_t i = 0; i < vertices; i++) {
        std::cout << KBLU << i << RST << " ";
        if (i < 10)
            std::cout << " ";

        for (size_t j = 0; j < count; j++) {
            std::cout << graph.at(i, j) << " ";

            if (graph.at(i, j) < 10 && graph.at(i, j) > -1)
                std::cout << "  ";
            else if (graph.at(i, j) > -10)
                std::cout << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}