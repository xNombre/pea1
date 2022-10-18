#include "CitiesMatrixPrinter.hpp"

#include <iostream>

using namespace std;

void separateWithSpaces(int number, size_t spaces)
{
    size_t digits = 0;
    if (number < 0)
        digits++;

    while (number > 0) {
        digits++;
        number %= 10;
    }

    for (size_t i = 0; i < spaces - digits; i++) {
        cout << " ";
    }
}

void CitiesMatrixPrinter::print(const ListGraph &graph)
{
    const auto &cities = graph.getVertexCount();
    for (size_t city = 0; city < cities; city++) {
        cout << city << " ";
        separateWithSpaces(city, 2);
    }
    cout << endl;

    for (size_t city = 0; city < cities; city++) {
        cout << "---";
    }
    cout << endl;
    
    for (size_t city = 0; city < cities; city++) {
        cout << city;
        separateWithSpaces(city, 2);
        cout << " | ";

        
    }
}