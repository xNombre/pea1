#include "BranchnBound.hpp"

#include "Array.hpp"

#include "CitiesMatrixPrinter.hpp"

auto BranchnBound::minimize_matrix(matrix_t matrix) -> reduce_result
{
    std::vector<size_t> min_col(matrix.get_cities_number(), unreachable_val);
    size_t reduce_factor = 0;

    for (size_t i = 0; i < matrix.get_cities_number(); i++) {
        size_t min_row = unreachable_val;
        for (size_t j = 0; j < matrix.get_cities_number() /*&& min_row != 0*/; j++) {
            if (matrix.at(i,j) < min_row) {
                min_row = matrix.at(i, j);
            }
            if (matrix.at(i, j) < min_col[j]) {
                min_col[j] = matrix.at(i, j);
            }
        }
        
        if (min_row != 0 || min_row != unreachable_val) {
            reduce_factor += min_row;
            // minimize row
            for (size_t j = 0; j < matrix.get_cities_number(); j++) {
                matrix.at(i,j) -= min_row;
            }
        }
    }

    // minimize columns
    for (size_t i = 0; i < min_col.size(); i++) {
        if (min_col[i] != 0 || min_col[i] != unreachable_val) {
            reduce_factor += min_col[i];
            for (size_t row = 0; row < min_col.size(); row++) {
                matrix.at(row, i) -= min_col[i];
            }
            /*for (auto &j : matrix[i]) {
                j -= min_col[i];
            }*/
        }
    }

    return { reduce_factor, matrix };
}

auto BranchnBound::mask_parent_and_current(matrix_t matrix, size_t from, size_t to) -> matrix_t
{
    for (size_t i = 0; i < matrix.get_cities_number(); i++) {
        matrix.at(from, i) = inf;
    }
    for (size_t i = 0; i < matrix.get_cities_number(); i++) {
        matrix.at(i, to) = inf;
    }
    matrix.at(to, from) = inf;

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

    throw std::runtime_error("You should never end up in here");
    //return result;
}