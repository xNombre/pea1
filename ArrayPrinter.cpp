#include "ArrayPrinter.hpp"

#include <iostream>

template<typename T>
void ArrayPrinter::print(const Array<T>& array)
{
    if (array.empty())
        return;
    
    for (size_t i = 0; i < array.size(); i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}