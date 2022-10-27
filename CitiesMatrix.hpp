#pragma once

#include <stddef.h>

class CitiesMatrix {
public:
    CitiesMatrix(const size_t &cities_number);
    CitiesMatrix() = default;
    ~CitiesMatrix();
    CitiesMatrix(CitiesMatrix &&);
    CitiesMatrix(CitiesMatrix &) = delete;
    CitiesMatrix(const CitiesMatrix &);
    CitiesMatrix &operator=(CitiesMatrix &&);
    CitiesMatrix &operator=(const CitiesMatrix &) = delete;

    void connect_cities(const size_t &from, const size_t &to, const size_t &weight);
    void connect_cities_bidirectional(const size_t &from, const size_t &to, const size_t &weight);

    bool is_matrix_valid() const;

    const int &at(const size_t &from, const size_t &to) const;
    int &at(const size_t &from, const size_t &to);

    const size_t &get_cities_number() const;

    void set_each_in_column(const size_t &column, const size_t &val);
    void set_each_in_row(const size_t &row, const size_t &val);

private:
    size_t cities_number = 0;
    int *matrix = nullptr;
};