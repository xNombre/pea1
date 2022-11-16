#include "DynamicTSP.hpp"

#include "ArrayPrinter.hpp"

TSPResult DynamicTSP::solve()
{
    TSPResult result;

    result.total_weight = recurse(1, 0);
    gen_path(1, 0);
    result.path = std::move(path);

    return result;
}

void DynamicTSP::gen_path(mask_t mask, size_t pos)
{
    if (mask == all_cities_mask) {
        return;
    }

    size_t city, cost = SIZE_MAX;
    for (size_t i = 0; i < matrix.get_cities_number(); i++) {
        mask_t cur_mask = (1 << i);
        if ((mask & cur_mask) != 0) {
            continue;
        }

        size_t new_cost = matrix.at(pos, i) + weights_matrix[(mask | cur_mask) * matrix.get_cities_number() + i];
        if (new_cost < cost) {
            cost = new_cost;
            city = i;
        }
    }

    path.push_back(city);
    gen_path((mask | (1 << city)), city);
}

size_t DynamicTSP::recurse(mask_t mask, size_t pos)
{
    if (mask == all_cities_mask) {
        return matrix.at(pos, 0);
    }

    size_t &cost = weights_matrix[mask * matrix.get_cities_number() + pos];

    if (cost != CitiesMatrix::unreachable_val) {
        return cost;
    }

    for (size_t i = 0; i < matrix.get_cities_number(); i++) {
        mask_t cur_mask = (1 << i);
        if ((mask & cur_mask) != 0) {
            continue;
        }

        if (cost == 0) {
            cost = matrix.at(pos, i) + recurse(mask | cur_mask, i);
        }
        else {
            cost = std::min(matrix.at(pos, i) + recurse(mask | cur_mask, i),
                            cost);
        }
    }

    return cost;
}