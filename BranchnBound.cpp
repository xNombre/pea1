#include "BranchnBound.hpp"

template<template <typename> typename Container>
size_t BranchnBound<Container>::minimize_matrix(matrix_t &matrix)
{
    std::vector<size_t> min_col(matrix.get_cities_number(), CitiesMatrix::unreachable_val);
    size_t reduce_factor = 0;

    for (size_t i = 0; i < matrix.get_cities_number(); i++) {
        weight_t min_row = CitiesMatrix::unreachable_val;
        for (size_t j = 0; j < matrix.get_cities_number(); j++) {
            if (matrix.at(i, j) < min_row) {
                min_row = matrix.at(i, j);
            }
            if (matrix.at(i, j) < min_col[j]) {
                min_col[j] = matrix.at(i, j);
            }
        }

        if (min_row == 0 || min_row == CitiesMatrix::unreachable_val) {
            continue;
        }

        reduce_factor += min_row;
        // minimize row
        for (size_t j = 0; j < matrix.get_cities_number(); j++) {
            if (matrix.at(i, j) == CitiesMatrix::unreachable_val)
                continue;

            matrix.at(i, j) -= min_row;

            min_col[j] = std::min(min_col[j], matrix.at(i, j));
        }

    }

    // minimize columns
    for (size_t i = 0; i < min_col.size(); i++) {
        if (min_col[i] == 0 || min_col[i] == CitiesMatrix::unreachable_val) {
            continue;
        }
        
        reduce_factor += min_col[i];
        for (size_t row = 0; row < min_col.size(); row++) {
            if (matrix.at(row, i) == CitiesMatrix::unreachable_val)
                continue;

            matrix.at(row, i) -= min_col[i];
        }

    }

    return reduce_factor;
}

template<template <typename> typename Container>
void BranchnBound<Container>::mask_parent_and_current(matrix_t &matrix, size_t from, size_t to)
{
    for (size_t i = 0; i < matrix.get_cities_number(); i++) {
        matrix.at(from, i) = CitiesMatrix::unreachable_val;
        matrix.at(i, to) = CitiesMatrix::unreachable_val;
    }
    matrix.at(to, from) = CitiesMatrix::unreachable_val;
}

template<template <typename> typename Container>
auto BranchnBound<Container>::process_node(Node parent, size_t to) -> Node
{
    parent.total_weight += parent.matrix.at(parent.city, to);
    mask_parent_and_current(parent.matrix, parent.city, to);
    parent.next_node(to, minimize_matrix(parent.matrix));

    return parent;
}

template<template <typename> typename Container>
void BranchnBound<Container>::queue_available_nodes(const Node &node)
{
    for (size_t i = 0; i < node.matrix.get_cities_number(); i++) {
        if (node.matrix.at(node.city, i) == CitiesMatrix::unreachable_val)
            continue;

        nodes_container.push(process_node(node, i));
    }
}

template<template <typename> typename Container>
auto BranchnBound<Container>::create_root_node(const CitiesMatrix &matrix) -> Node
{
    auto minimized_matrix = matrix;
    auto cost = minimize_matrix(minimized_matrix);

    Node root_node(matrix.get_cities_number(), 0);
    root_node.matrix = std::move(minimized_matrix);
    root_node.city = 0;
    root_node.total_weight = cost;

    return root_node;
}

template<template <typename> typename Container>
template<typename T>
typename std::enable_if<std::is_same<Container<T>, std::queue<T>>::value, T>::type
constexpr BranchnBound<Container>::get_queue_top_node()
{
    return nodes_container.front();
}

template<template <typename> typename Container>
template<typename T>
typename std::enable_if<std::is_same<Container<T>, std::stack<T>>::value, T>::type
constexpr BranchnBound<Container>::get_queue_top_node()
{
    return nodes_container.top();
}

template<template <typename> typename Container>
template<typename T>
typename std::enable_if<std::is_same<Container<T>, std::priority_queue<T>>::value, T>::type
constexpr BranchnBound<Container>::get_queue_top_node()
{
    return nodes_container.top();
}

template<template <typename> typename Container>
TSPResult BranchnBound<Container>::solve()
{
    const auto &matrix = *this->matrix;
    TSPResult result;
    if constexpr (!std::is_same<Container<Node>, std::priority_queue<Node>>::value) {
        result.total_weight = SIZE_MAX;
    }

    queue_available_nodes(create_root_node(matrix));

    while (!nodes_container.empty()) {
        Node cur = get_queue_top_node<Node>();
        nodes_container.pop();

        if constexpr (!std::is_same<Container<Node>, std::priority_queue<Node>>::value) {
            if (result.total_weight < cur.total_weight) {
                continue;
            }
        }

        if (cur.cities_left == 1) {
            if constexpr (std::is_same<Container<Node>, std::priority_queue<Node>>::value) {
                result.path = cur.path;
                result.total_weight = cur.total_weight;
                return result;
            }
            else {
                if (result.total_weight > cur.total_weight) {
                    result.path = cur.path;
                    result.total_weight = cur.total_weight;
                }
                continue;
            }
        }

            queue_available_nodes(cur);
    }

    if constexpr (std::is_same<Container<Node>, std::priority_queue<Node>>::value) {
        throw std::runtime_error("Something went terribly wrong");
    }
    else {
        return result;
    }
}