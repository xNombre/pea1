#pragma once

#include <vector>
#include <queue>
#include <stack>

#include "Array.hpp"
#include "TSPAlgorithm.hpp"

template<template <typename Type> typename Container>
class BranchnBound : public TSPAlgorithm {
public:
    BranchnBound(const CitiesMatrix &matrix)
        : TSPAlgorithm(matrix)
    { }

    TSPResult solve() override;

    ~BranchnBound() = default;

private:
    typedef CitiesMatrix matrix_t;
    struct Node;
    Container<Node> nodes_container;

    size_t minimize_matrix(matrix_t &matrix);
    void mask_parent_and_current(matrix_t &matrix, size_t from, size_t to);
    void queue_available_nodes(const Node &node);

    template<typename T>
    typename std::enable_if<std::is_same<Container<T>, std::queue<T>>::value, T>::type
    constexpr get_queue_top_node();

    template<typename T>
    typename std::enable_if<std::is_same<Container<T>, std::stack<T>>::value, T>::type
    constexpr get_queue_top_node();

    template<typename T>
    typename std::enable_if<std::is_same<Container<T>, std::priority_queue<T>>::value, T>::type
    constexpr get_queue_top_node();

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

template class BranchnBound<std::priority_queue>;
template class BranchnBound<std::stack>;
template class BranchnBound<std::queue>;