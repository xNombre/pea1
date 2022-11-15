#include "QuickPermArray.hpp"

QuickPermArray::QuickPermArray(const size_t &cities_count)
    : permutation_array(cities_count),
      iteration_state(cities_count + 1)
{
    for (size_t i = 0; i < cities_count; i++) {
        permutation_array[i] = i + 1;
        iteration_state[i] = i;
    }
    iteration_state[cities_count] = cities_count;
}

const size_t &QuickPermArray::operator[](const size_t &index) const
{
#ifdef DEBUG
    if (index >= permutation_array.size()) {
        throw std::out_of_range("Index out of range");
    }
#endif

    return permutation_array[index];
}

bool QuickPermArray::next_permutation()
{
    if (index >= permutation_array.size()) {
        return false;
    }

    iteration_state[index]--;

    const size_t& j = (index % 2) * iteration_state[index];

    const auto tmp = permutation_array[j];
    permutation_array[j] = permutation_array[index];
    permutation_array[index] = tmp;

    index = 1;
    while (iteration_state[index] == 0) {
        iteration_state[index] = index;
        index++;
    }

    return true;
}

const Array<size_t> &QuickPermArray::get_array() const
{
    return permutation_array;
}