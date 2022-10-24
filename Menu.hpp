#pragma once

#include <iostream>

#include "CitiesGraphReader.hpp"
#include "CitiesMatrixPrinter.hpp"
#include "BruteForceTSP.hpp"
#include "ArrayPrinter.hpp"
#include "BranchnBound.hpp"
#include "RandomGraphGen.hpp"
#include "DynamicTSP.hpp"
#include "TimeBench.hpp"

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

void print_result(const TSPResult& result)
{
    std::cout << result.total_weight << std::endl;
    ArrayPrinter::print(result.path);
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
            << "a - branch&bound (little)\n"
            << "d - dynamic\n"
            << "s - benchmark\n"
            << "e - wyjscie\n";
        input = getOptionFromUser();

        switch (input) {
        case 'r': {
            auto size = getDataFromUser();
            graph = RandomGraphGen::generate(size);
            break;
        }
        case 'f': {
            string file;
            cin >> file;
            graph = CitiesGraphReader::readFromFile(file);
            break;
        }
        case 'x': {
            CitiesMatrixPrinter::print(graph);
            break;
        }
        case 'b': {
            TSPAlgorithm *alg = new BruteForceTSP(graph);
            print_result(alg->solve());
            break;
        }
        case 'a': {
            TSPAlgorithm *alg = new BranchnBound(graph);
            print_result(alg->solve());
            break;
        }
        case 'd': {
            TSPAlgorithm *alg = new DynamicTSP(graph);
            print_result(alg->solve());
            break;
        }
        case 'e': {
            return;
        }
        case 's': {
            break;
        }
        }
    }
}