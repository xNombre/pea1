#pragma once

#include <fstream>

#include "ListGraph.hpp"

class CitiesGraphReader {
public:
    static ListGraph readFromFile(const std::string& filename);
private:
    static std::ifstream openFile(const std::string &filename);
    static ListGraph readCostsMatrix(std::ifstream &fileStream, const size_t &citiesCount);
};