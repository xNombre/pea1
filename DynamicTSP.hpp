#pragma once

#include "TSPAlgorithm.hpp"
#include <vector>
#include <math.h>

class DynamicTSP : public TSPAlgorithm {
    typedef size_t mask_t;
    
public:
    DynamicTSP(const CitiesMatrix &matrix)
        : TSPAlgorithm(matrix),
        cities_pow(std::pow(2, matrix.get_cities_number())),
        weights_matrix(std::pow(2, matrix.get_cities_number()) *matrix.get_cities_number(), CitiesMatrix::unreachable_val)
    {
        if (matrix.get_cities_number() > sizeof(mask_t) * 8) {
            throw std::runtime_error("Cities size is larger than mask size");
        }
        
        all_cities_mask = (1 << matrix.get_cities_number()) - 1;
    }

    TSPResult solve() override;

private:
    std::vector<size_t> weights_matrix;
    mask_t all_cities_mask;
    size_t cities_pow;
    Array<size_t> path;

    size_t recurse(mask_t mask, size_t pos);
    void gen_path(mask_t mask, size_t pos);
};