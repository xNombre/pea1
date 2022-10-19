#pragma once

#include "TSPAlgorithm.hpp"

class BruteForceTSP : public TSPAlgorithm {
public:
    BruteForceTSP(const CitiesMatrix &matrix)
        : TSPAlgorithm(matrix)
    {
    }
    
    TSPResult solve() override;
};