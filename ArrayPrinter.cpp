#include "ArrayPrinter.hpp"

#include <iostream>

template<typename T>
void ArrayPrinter<T>::print(const Array<T>& array)
{
    for (size_t i = 0; i < array.size(); i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}