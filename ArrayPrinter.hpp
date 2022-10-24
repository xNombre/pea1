#pragma once

#include <iostream>

#include "Array.hpp"

class ArrayPrinter {
public:
    template <typename T>
    static void print(const Array<T> &array)
    {
        if (array.empty())
            return;

        for (size_t i = 0; i < array.size(); i++) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }
};
