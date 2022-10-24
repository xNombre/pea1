#pragma once

#include <vector>
#include <queue>
#include <stack>

#include "TSPAlgorithm.hpp"

class BranchnBound : public TSPAlgorithm {
public:
    BranchnBound(const CitiesMatrix &matrix)
        : TSPAlgorithm(matrix)
    {
    }

    TSPResult solve() override;

private:
    typedef std::vector<std::vector<size_t>> matrix_t;
    typedef std::pair<size_t, matrix_t> reduce_result;
    const size_t& inf = SIZE_MAX;

    reduce_result BranchnBound::minimize_matrix(matrix_t matrix);
};