#include "BruteForceTSP.hpp"

#include "QuickPermArray.hpp"

TSPResult BruteForceTSP::solve()
{
    TSPResult result;

    const auto iterations = matrix.get_cities_number() - 1, last = matrix.get_cities_number() - 2;
    QuickPermArray perm(iterations);
    result.total_weight = SIZE_MAX;

    do {
        size_t cur_weight = matrix.at(0, perm[0]);

        for (size_t i = 0, j = 1; i < iterations; i++, j++) {
            cur_weight += matrix.at(perm[i], perm[j]);
        }
        cur_weight += matrix.at(perm[last], 0);

        if (result.total_weight > cur_weight) {
            result.total_weight = cur_weight;
            result.path = perm.get_array();
        }
    } while (perm.next_permutation());
    
    return result;
}