#pragma once

#include "Array.hpp"

template <typename T>
class ArrayPrinter {
public:
    static void print(const Array<T> &array);
};

#include "ArrayPrinter.cpp"