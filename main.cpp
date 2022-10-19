#include <iostream>

#include "Array.hpp"
#include "ArrayPrinter.hpp"
#include "CitiesMatrixPrinter.hpp"
#include "CitiesMatrix.hpp"
#include "QuickPermArray.hpp"

#include "Menu.hpp"

int main()
{
    //menu();
    QuickPermArray perm(9);
    int a = 0;
    do {
        for (int i = 0; i < 3; i++) {
            std::cout << perm[i];
        }
        std::cout << std::endl;
        a++;
    } while (perm.next_permutation());
    cout << a << std::endl;

    return 0;
}