#include "BruteForceTSP.hpp"

#include "QuickPermArray.hpp"

#include <iostream>
using namespace std;

TSPResult BruteForceTSP::solve()
{
    TSPResult result;

    const auto &matrix = *this->matrix;
    QuickPermArray perm(matrix.get_cities_number() - 1);
    size_t min = SIZE_MAX;

    do {
        size_t cur_weight = 0;
        cur_weight += matrix.at(0, perm[0] + 1);
        for (size_t i = 1; i < matrix.get_cities_number() - 1; i++) {
            cur_weight += matrix.at(perm[i - 1] + 1, perm[i] + 1);
        }
        cur_weight += matrix.at(perm[matrix.get_cities_number() - 2] + 1, 0);

        if (min > cur_weight) {
            min = cur_weight;
        }
    } while (perm.next_permutation());

    result.total_weight = min;
    
    return result;
}