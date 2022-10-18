#include <iostream>

#include "CitiesGraphReader.hpp"

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

int menu()
{
    char input;
    cout << "PEA Projekt 1.\n"
        << "f - odczyt z pliku\n"
        << "r - losowa generacja\n"
        << "x - wyswietl graf";
    input = getOptionFromUser();

    ListGraph graph;

    switch (input) {
    case 'f':
        break;
    case 'r':
        string file;
        cin >> file;
        graph = CitiesGraphReader::readFromFile(file);
        break;
    }
    
    return 0;
}