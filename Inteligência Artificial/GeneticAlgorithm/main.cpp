#include <iostream>
#include <cstdlib>
#include <ctime>
#include "algoritmo_genetico.h"

int main() {
    std::srand(std::time(nullptr));

    AlgoritmoGenetico ag(100, 20);

    return 0;
}
