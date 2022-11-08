#pragma once

#include <vector>
#include <queue>
#include <stack>

#include "Array.hpp"
#include "TSPAlgorithm.hpp"

template<typename Container>
class BranchnBound : public TSPAlgorithm {
public:
    BranchnBound(const CitiesMatrix &matrix)
        : TSPAlgorithm(matrix)
    {
    }

    TSPResult solve() override;

    ~BranchnBound() = default;
private:
    typedef CitiesMatrix matrix_t;
    struct Node;
    Container nodes_container;

    size_t minimize_matrix(matrix_t &matrix);
    size_t minimize_rows_by(matrix_t &matrix,
                          const size_t factor,
                          std::vector<size_t> &columns_reduce);
    size_t minimize_columns_by_array(matrix_t &matrix, const std::vector<size_t>& columns_reduce);
    void mask_parent_and_current(matrix_t &matrix, size_t from, size_t to);
    template<template<typename T> typename container>
    void queue_available_nodes(container<Node> &cont,
                               Node &node);
    Node create_root_node(const CitiesMatrix &matrix);
    Node process_node(Node parent, size_t to);

    struct Node {
        size_t total_weight = 0;
        Array<size_t> path;
        matrix_t matrix;
        size_t city;
        size_t cities_left;

        Node(const size_t cities, const size_t city)
        {
            cities_left = cities;
            this->city = city;
        }

        void next_node(const size_t next, const size_t weight)
        {
            path.push_back(next);
            total_weight += weight;
            cities_left--;
            city = next;
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