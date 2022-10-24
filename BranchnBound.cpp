#include "BranchnBound.hpp"

auto BranchnBound::minimize_matrix(matrix_t matrix) -> reduce_result
{
    std::vector<size_t> min_col(matrix.size(), SIZE_MAX);
    size_t reduce_factor = 0;

    for (auto i : matrix) {
        size_t min_row = SIZE_MAX;
        for (size_t j = 0; j < i.size(); j++) {
            if (i[j] < min_row) {
                min_row = j;
            }
            if (i[j] < min_col[j]) {
                min_col[j] = i[j];
            }
        }
        if (min_row != 0) {
            reduce_factor += min_row;
            // minimize row
            for (auto& j : i) {
                j -= min_row;
            }
        }
    }

    // minimize columns
    for (int i = 0; i < min_col.size(); i++) {
        if (i != 0) {
            reduce_factor += min_col[i];
            for (auto &j : matrix[i]) {
                j -= min_col[i];
            }
        }
    }

    return { reduce_factor, matrix };
}

TSPResult BranchnBound::solve()
{
    TSPResult result;



    return result;
}