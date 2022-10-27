#include "BranchnBound.hpp"

auto BranchnBound::minimize_matrix(matrix_t matrix) -> reduce_result
{
    std::vector<size_t> min_col(matrix.get_cities_number(), SIZE_MAX);
    size_t reduce_factor = 0;

    /*for (auto i : matrix) {
        size_t min_row = SIZE_MAX;
        for (size_t j = 0; j < i.size(); j++) {
            if (i[j] < min_row) {
                min_row = j;
            }
            if (i[j] < min_col[j]) {
                min_col[j] = i[j];
            }
        }
        if (min_row != 0) {
            reduce_factor += min_row;
            // minimize row
            for (auto &j : i) {
                j -= min_row;
            }
        }
    }

    // minimize columns
    for (int i = 0; i < min_col.size(); i++) {
        if (i != 0) {
            reduce_factor += min_col[i];
            for (auto &j : matrix[i]) {
                j -= min_col[i];
            }
        }
    }*/

    return { reduce_factor, matrix };
}

auto BranchnBound::mask_parent_and_current(matrix_t matrix, size_t from, size_t to) -> matrix_t
{
    /*for (auto &row : matrix[from]) {
        row = inf;
    }
    for (auto &col : matrix[to]) {
        col = inf;
    }
    matrix[to][from] = inf;*/

    return matrix;
}

TSPResult BranchnBound::solve()
{
    TSPResult result;

    std::priority_queue<Node> queue;

    const auto &matrix = *this->matrix;

    auto minimize_result = minimize_matrix(matrix);
    auto &minimized_matrix = minimize_result.second;
    auto &cost = minimize_result.first;

    for (int i = 0; i < matrix.get_cities_number(); i++) {
        Node node(matrix.get_cities_number(), i);
        node.next_node(0, matrix.at(0, i));
        queue.push(node);
    }

    while (!queue.empty()) {
        auto &cur = queue.top();
        queue.pop();

        if (cur.cities_left == 0) {
            // finish here?

            continue;
        }

        for (int i = 0; i < matrix.get_cities_number(); i++) {
            if (cur.matrix.at(cur.city, i) == inf)
                continue;

            auto masked = mask_parent_and_current(cur.matrix, cur.city, i);

            auto minimize_result = minimize_matrix(matrix);
            auto &minimized_matrix = minimize_result.second;
            auto &cost = minimize_result.first;

            Node node(matrix.get_cities_number(), i);
            node.path = cur.path;
            node.path.push_back(cur.city);
            //node.total_weight
        }
    }

    return result;
}