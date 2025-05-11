#define HELLOWORLD_EXPORTS
#include "NewScript1.h"
#include <iostream>

// Implementacja funkcji, która będzie eksportowana z DLL
void HelloWorld() {
    std::cout << "DLL v1.0 dziala" << std::endl;
}
