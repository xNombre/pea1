#pragma once

#include "Array.hpp"

class QuickPermArray {
public:
    QuickPermArray(const size_t &cities_count);
    const size_t &operator[](const size_t &index) const;

    // Returns false when there are no more permutations
    bool next_permutation();

private:
    Array<size_t> permutation_array;
    Array<size_t> iteration_state;
    size_t index = 1;
};