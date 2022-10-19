#pragma once

#include <iostream>

#include "CitiesGraphReader.hpp"
#include "CitiesMatrixPrinter.hpp"
#include "BruteForceTSP.hpp"

using namespace std;

long long getDataFromUser()
{
    long long val;
    //cout << "Podaj wartosc:\n";
    cin >> val;

    // Clear any garbage
    cin.clear();
    cin.ignore(10000, '\n');

    return val;
}

char getOptionFromUser()
{
    char input;
    std::cin >> input;

    // Clear any garbage
    cin.clear();
    cin.ignore(10000, '\n');

    return input;
}

void menu()
{
    CitiesMatrix graph;
    while (1) {
        char input;
        cout << "PEA Projekt 1.\n"
            << "f - odczyt z pliku\n"
            << "r - losowa generacja\n"
            << "x - wyswietl graf\n"
            << "b - brute-force\n"
            << "a - branch&bount\n"
            << "x - \n";
        input = getOptionFromUser();


        switch (input) {
        case 'r':
            break;
        case 'f': {
            string file;
            cin >> file;
            graph = CitiesGraphReader::readFromFile(file);
            break;
        }
        case 'x':
            CitiesMatrixPrinter::print(graph);
            break;
        case 'b': {
            BruteForceTSP alg = BruteForceTSP(graph);
            std::cout << alg.solve().total_weight << std::endl;
            return;
        }
        }
    }
}