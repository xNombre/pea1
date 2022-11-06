#pragma once

#include <iostream>
#include <memory>

#include "CitiesGraphReader.hpp"
#include "CitiesMatrixPrinter.hpp"
#include "BruteForceTSP.hpp"
#include "ArrayPrinter.hpp"
#include "BranchnBound.hpp"
#include "RandomGraphGen.hpp"
#include "DynamicTSP.hpp"
#include "TimeBench.hpp"
#include "TimeBench.cpp"

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

void solve_tsp(std::unique_ptr<TSPAlgorithm> alg)
{
    using namespace std::chrono_literals;
    TimeBench<TSPResult> benchmark([&] { return alg->solve(); });
    auto result_fut = benchmark.start_benchmark(5min);
    auto result = result_fut.get();
    print_result(result.result);
    std::cout << "Finished in " <<
        std::chrono::duration_cast<std::chrono::milliseconds>(result.measured_time).count()
        << "ms" << std::endl;
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
            solve_tsp(std::make_unique<BruteForceTSP>(graph));
            break;
        }
        case 'a': {
            solve_tsp(std::make_unique<BranchnBound>(graph));
            break;
        }
        case 'd': {
            solve_tsp(std::make_unique<DynamicTSP>(graph));
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