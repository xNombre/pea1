#include "CitiesMatrix.hpp"

#include <stdexcept>

CitiesMatrix::CitiesMatrix(const size_t &cities_number)
    : cities_number(cities_number)
{
    matrix = new int[cities_number * cities_number]();

    for (int i = 0; i < cities_number; i++) {
        at(i, i) = -1;
    }
}

CitiesMatrix::~CitiesMatrix()
{
    delete[] matrix;
}

CitiesMatrix::CitiesMatrix(CitiesMatrix &&other)
{
    cities_number = other.cities_number;
    matrix = other.matrix;

    other.matrix = nullptr;
    other.cities_number = 0;
}

CitiesMatrix &CitiesMatrix::operator=(CitiesMatrix &&other)
{
    delete[] matrix;
    
    cities_number = other.cities_number;
    matrix = other.matrix;

    other.matrix = nullptr;
    other.cities_number = 0;

    return *this;
}

void CitiesMatrix::connect_cities(const size_t &from, const size_t &to, const size_t &weight)
{
#ifdef DEBUG
    if (from == to)
        throw std::invalid_argument("");
#endif // DEBUG

    at(from, to) = weight;
}

void CitiesMatrix::connect_cities_bidirectional(const size_t &from,
                                                const size_t &to,
                                                const size_t &weight)
{
    connect_cities(from, to, weight);
    connect_cities(to, from, weight);
}

bool CitiesMatrix::is_matrix_valid() const
{
    for (int i = 0; i < cities_number; i++) {
        for (int j = 0; j < cities_number; j++) {
            if (at(i, j) == 0)
                return false;
            if (at(i, j) == -1 && i != j)
                return false;
        }
    }

    return true;
}

const int &CitiesMatrix::at(const size_t &from, const size_t &to) const
{
#ifdef DEBUG
    if (!matrix)
        throw std::runtime_error("Matix is null!");

    if (from >= cities_number || to >= cities_number)
        throw std::out_of_range("");
#endif // DEBUG

    return matrix[from * cities_number + to];
}

int &CitiesMatrix::at(const size_t &from, const size_t &to)
{
#ifdef DEBUG
    if (!matrix)
        throw std::runtime_error("Matix is null!");
    
    if (from >= cities_number || to >= cities_number)
        throw std::out_of_range("");
#endif // DEBUG

    return matrix[from * cities_number + to];
}

const size_t &CitiesMatrix::get_cities_number() const
{
    return cities_number;
}