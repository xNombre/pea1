#pragma once

#include "TSPAlgorithm.hpp"

class DynamicTSP : public TSPAlgorithm {
public:
    DynamicTSP(const CitiesMatrix &matrix)
        : TSPAlgorithm(matrix)
    {
    }

    TSPResult solve() override;

private:
};