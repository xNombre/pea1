#include "BranchnBound.hpp"

#include "Array.hpp"

#include "CitiesMatrixPrinter.hpp"

size_t BranchnBound::minimize_matrix(matrix_t &matrix)
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

size_t BranchnBound::minimize_rows_by(matrix_t &matrix,
                                      const size_t factor,
                                      std::vector<size_t> &columns_reduce)
{
    size_t reduce_factor = 0;

    if (factor != 0 && factor != CitiesMatrix::unreachable_val) {
        reduce_factor += factor;
        // minimize row
        for (size_t j = 0; j < matrix.get_cities_number(); j++) {
            //if (matrix.at(i, j) == CitiesMatrix::unreachable_val)
                continue;

            //matrix.at(i, j) -= factor;

            //columns_reduce[j] = std::min(columns_reduce[j], matrix.at(i, j));
        }
    }

    return reduce_factor;
}

size_t BranchnBound::minimize_columns_by_array(matrix_t &matrix,
                                               const std::vector<size_t> &columns_reduce)
{
    size_t reduce_factor = 0;

    for (size_t i = 0; i < columns_reduce.size(); i++) {
        if (columns_reduce[i] != 0 && columns_reduce[i] != CitiesMatrix::unreachable_val) {
            reduce_factor += columns_reduce[i];
            for (size_t row = 0; row < columns_reduce.size(); row++) {
                if (matrix.at(row, i) == CitiesMatrix::unreachable_val)
                    continue;

                matrix.at(row, i) -= columns_reduce[i];
            }
        }
    }

    return reduce_factor;
}

void BranchnBound::mask_parent_and_current(matrix_t &matrix, size_t from, size_t to)
{
    for (size_t i = 0; i < matrix.get_cities_number(); i++) {
        matrix.at(from, i) = CitiesMatrix::unreachable_val;
        matrix.at(i, to) = CitiesMatrix::unreachable_val;
    }
    matrix.at(to, from) = CitiesMatrix::unreachable_val;
}

auto BranchnBound::process_node(Node parent, size_t to) -> Node
{
    parent.total_weight += parent.matrix.at(parent.city, to);
    mask_parent_and_current(parent.matrix, parent.city, to);
    parent.next_node(to, minimize_matrix(parent.matrix));

    return parent;
}

template<template<typename T> typename container>
void BranchnBound::queue_available_nodes(container<Node> &cont,
                                         Node &node)
{
    for (int i = 0; i < node.matrix.get_cities_number(); i++) {
        if (node.matrix.at(node.city, i) == CitiesMatrix::unreachable_val)
            continue;

        cont.push(process_node(node, i));
    }
}

auto BranchnBound::create_root_node(const CitiesMatrix &matrix) -> Node
{
    auto minimized_matrix = matrix;
    auto cost = minimize_matrix(minimized_matrix);

    Node root_node(matrix.get_cities_number(), 0);
    root_node.matrix = std::move(minimized_matrix);
    root_node.city = 0;
    root_node.total_weight = cost;

    return root_node;
}

template<typename Container>
TSPResult BranchnBound::solve()
{
    TSPResult result;
    std::priority_queue<Node> queue;
    const auto &matrix = *this->matrix;

    auto root_node = create_root_node(matrix);
    queue_available_nodes(queue, root_node);

    while (!queue.empty()) {
        auto cur = queue.top();
        queue.pop();

        if (cur.cities_left == 0) {
            // check if there is any more promising path
            // not needed with priority queue
            /*for (auto candidate : queue) {
                continue;
            }*/

            // return current path when theres no better path
            result.path = cur.path;
            result.total_weight = cur.total_weight;
            return result;
        }

        queue_available_nodes(queue, cur);
    }

    throw std::runtime_error("Something went terribly wrong");
}