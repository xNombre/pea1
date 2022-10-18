#pragma once

#include "Array.hpp"

class ArrayPrinter {
public:
    template <typename T>
    static void print(const Array<T> &array);
};

//#include "ArrayPrinter.cpp"