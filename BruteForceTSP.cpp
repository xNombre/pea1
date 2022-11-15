#include "BruteForceTSP.hpp"

#include "QuickPermArray.hpp"

TSPResult BruteForceTSP::solve()
{
    TSPResult result;

    const auto &matrix = *this->matrix;
    QuickPermArray perm(matrix.get_cities_number() - 1);
    result.total_weight = SIZE_MAX;

    do {
        size_t cur_weight;
    
        cur_weight = matrix.at(0, perm[0]);
        for (size_t i = 1, j = 0; i < matrix.get_cities_number() - 1 && cur_weight < result.total_weight; i++, j++) {
            cur_weight += matrix.at(perm[j], perm[i]);
        }
        cur_weight += matrix.at(perm[matrix.get_cities_number() - 2], 0);

        if (result.total_weight > cur_weight) {
            result.total_weight = cur_weight;
            result.path = perm.get_array();
        }
    } while (perm.next_permutation());
    
    return result;
}