#pragma once

#include <vector>
#include <queue>
#include <stack>

#include "Array.h"
#include "TSPAlgorithm.hpp"

class BranchnBound : public TSPAlgorithm {
public:
    BranchnBound(const CitiesMatrix &matrix)
        : TSPAlgorithm(matrix)
    {
    }

    TSPResult solve() override;

private:
    typedef CitiesMatrix matrix_t;
    typedef std::pair<size_t, matrix_t> reduce_result;

    reduce_result minimize_matrix(matrix_t matrix);
    matrix_t mask_parent_and_current(matrix_t matrix, size_t from, size_t to);

    struct Node {
        size_t total_weight = 0;
        Array<size_t> path;
        matrix_t matrix;
        size_t city;
        size_t cities_left;

        Node(const size_t &cities, const size_t &city)
        {
            cities_left = cities;
            this->city = city;
        }

        void next_node(const size_t &next, const size_t &weight)
        {
            path.push_back(next);
            total_weight += weight;
            cities_left--;
        }

        // Reverse comparison operators to prioritize cheaper weights
        bool operator>(const Node &other) const
        {
            return total_weight < other.total_weight;
        }
        bool operator<(const Node &other) const
        {
            return total_weight > other.total_weight;
        }
    };
};