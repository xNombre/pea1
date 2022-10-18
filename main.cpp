#include <iostream>

#define DEBUG

#include "Array.hpp"
#include "ArrayPrinter.hpp"

int main()
{
    Array<int> test;
    test.push_back(11);
    ArrayPrinter<int>::print(test);    

    return 0;
}